/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthan <dthan@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/28 22:17:58 by dthan             #+#    #+#             */
/*   Updated: 2021/01/28 02:59:27 by dthan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static void	here_doc_prepare_the_end_word_with_enter(
		char end_word_with_enter[256], char *end_word)
{
	ft_bzero(end_word_with_enter, 256);
	ft_strcpy(end_word_with_enter, end_word);
	ft_strcat(end_word_with_enter, "\n");
}

char		*get_heredoc(char *end_word)
{
	t_phase		phase;
	char		*heredoc;
	char		*line;
	t_prompt	prompt_type;
	char		end_word_with_enter[256];

	heredoc = ft_strnew(0);
	phase = PHASE_HEREDOC;
	prompt_type = PROMPT_HEREDOC;
	here_doc_prepare_the_end_word_with_enter(end_word_with_enter, end_word);
	while ("getting heredoc")
	{
		if ((line = ft_get_line(&phase, prompt_type, LEX_HEREDOC)) == NULL)
		{
			free(heredoc);
			return (NULL);
		}
		if (phase == PHASE_STOP || ft_strequ(line, end_word_with_enter))
		{
			free(line);
			break ;
		}
		heredoc = ft_strjoin_and_free_2strings(heredoc, line);
	}
	return (heredoc);
}

static void	add_heredoc_into_list(t_heredoc *node, t_heredoc **list)
{
	t_heredoc *ptr;

	if (*list == NULL)
		*list = node;
	else
	{
		ptr = *list;
		while (ptr->next)
			ptr = ptr->next;
		ptr->next = node;
	}
}

static int	apply_heredoc(t_astnode *here_end)
{
	char		*current_heredoc;
	t_heredoc	*node;

	if ((current_heredoc = get_heredoc(here_end->data)) == NULL)
		return (EXIT_FAILURE);
	node = ft_memalloc(sizeof(t_heredoc));
	node->doc = current_heredoc;
	node->next = NULL;
	add_heredoc_into_list(node, &g_shell.heredoc_lst);
	return (EXIT_SUCCESS);
}

int			find_heredoc(t_astnode *ast)
{
	if (ast == NULL)
		return (EXIT_SUCCESS);
	else if (ast->type == AST_complete_command)
		return (find_heredoc(ast->left));
	else if (ast->type == AST_list ||
			ast->type == AST_and_or ||
			ast->type == AST_pipe_sequence)
	{
		if (find_heredoc(ast->left) == EXIT_FAILURE)
			return (EXIT_FAILURE);
		return (find_heredoc(ast->right));
	}
	else if (ast->type == AST_simple_command)
		return (find_heredoc(ast->right));
	else if (ast->type == AST_cmd_suffix)
	{
		if (find_heredoc(ast->left) == EXIT_FAILURE)
			return (EXIT_FAILURE);
		return (find_heredoc(ast->right));
	}
	else if (ast->type == AST_io_redirect)
		return (find_heredoc(ast->left));
	else if (ast->type == AST_io_here && ft_strequ(ast->data, "<<"))
		return (apply_heredoc(ast->left));
	return (EXIT_SUCCESS);
}
