/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthan <dthan@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/28 22:17:58 by dthan             #+#    #+#             */
/*   Updated: 2021/01/07 04:12:59 by dthan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

char *get_heredoc(char *end_word)
{
	t_phase phase;
	char *heredoc;
	char *line;
	int prompt_len;

	heredoc = ft_strnew(0);
	phase = PHASE_HEREDOC;
	while ("getting heredoc")
	{
		prompt_len = ft_printf("heredoc> ");
		if ((line = ft_get_line(&phase, prompt_len, LEX_HEREDOC)) == NULL)
		{
			free(heredoc);
			return (NULL);
		}
		if (phase == PHASE_STOP || ft_strnequ(line, end_word, ft_strlen(end_word)))
		{
			free(line);
			break ;
		}
		heredoc = ft_strjoin_and_free_2strings(heredoc, line);
	}
	return (heredoc);
}

/*
static char			*prompt_heredoc(char *end_word)
{
	t_l				l;

	ft_memset(&l, 0, sizeof(t_l));
	// l.phase = EDTR_PHASE_HEREDOC;
	l.pmpt = 9;
	ft_putstr("heredoc> ");
	ft_get_line(&l);
	if (ft_strequ(l.line, end_word) || ft_strequ(l.line, "\x04"))
	{
		ft_strdel(&l.line);
		return (NULL);
	}
	else
	{
		l.line = ft_strjoin_and_free_string1(l.line, "\n");
		l.line = ft_strjoin_and_free_2strings(l.line, prompt_heredoc(end_word));
	}
	return (l.line);
}
*/

static void			add_heredoc_into_list(t_heredoc *node, t_heredoc **list)
{
	t_heredoc *ptr;

	if (node == NULL || *list == NULL)
		return ;
	ptr = *list;
	while (ptr->next)
		ptr = ptr->next;
	ptr->next = node;
}

static int			apply_heredoc(t_astnode *here_end)
{
	char 	*current_heredoc;
	t_heredoc	*node;

	if ((current_heredoc = get_heredoc(here_end->data)) == NULL)
		return (EXIT_FAILURE);
	node = ft_memalloc(sizeof(t_heredoc));
	node->doc = current_heredoc;
	node->next = NULL;
	if (g_shell.first_heredoc == NULL)
		g_shell.first_heredoc = node;
	else
		add_heredoc_into_list(node, &g_shell.heredoc_lst);
	return (EXIT_SUCCESS);
}

int				find_heredoc(t_astnode *ast)
{
	if (ast->type == AST_complete_command)
		return (find_heredoc(ast->left));
	else if (ast->type == AST_list || ast->type == AST_and_or || \
			ast->type == AST_pipe_sequence || ast->type == AST_cmd_suffix)
	{
		if (find_heredoc(ast->left) == EXIT_FAILURE)
			return (EXIT_FAILURE);
		return (find_heredoc(ast->right));
	}
	else if (ast->type == AST_simple_command)
		return (find_heredoc(ast->right));
	else if (ast->type == AST_io_redirect)
		return (find_heredoc(ast->left));
	else if (ast->type == AST_io_here && ft_strequ(ast->data, "<<"))
		return (apply_heredoc(ast->left));
	return (EXIT_SUCCESS);
}

void				clear_heredoc(t_heredoc *heredoc)
{
	t_heredoc *container;

	while(heredoc)
	{
		container = heredoc;
		heredoc = heredoc->next;
		free(container->doc);
		free(container);
	}
}
