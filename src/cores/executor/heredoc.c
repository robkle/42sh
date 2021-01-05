/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthan <dthan@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/28 22:17:58 by dthan             #+#    #+#             */
/*   Updated: 2021/01/05 15:52:42 by dthan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
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

static void			apply_heredoc(t_astnode *here_end)
{
	char 	*current_heredoc;
	t_heredoc	*node;

	current_heredoc = prompt_heredoc(here_end->data);
	node = ft_memalloc(sizeof(t_heredoc));
	node->doc = current_heredoc;
	node->next = NULL;
	if (g_shell.first_heredoc == NULL)
		g_shell.first_heredoc = node;
	else
		add_heredoc_into_list(node, &g_shell.first_heredoc);
}

void				find_heredoc(t_astnode *ast)
{
	if (ast->type == AST_complete_command)
		find_heredoc(ast->left);
	else if (ast->type == AST_list || ast->type == AST_and_or || \
			ast->type == AST_pipe_sequence || ast->type == AST_cmd_suffix)
	{
		find_heredoc(ast->left);
		find_heredoc(ast->right);
	}
	else if (ast->type == AST_simple_command)
		find_heredoc(ast->right);
	else if (ast->type == AST_io_redirect)
		find_heredoc(ast->left);
	else if (ast->type == AST_io_here && ft_strequ(ast->data, "<<"))
		apply_heredoc(ast->left);
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
*/