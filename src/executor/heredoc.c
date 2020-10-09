/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthan <dthan@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/28 22:17:58 by dthan             #+#    #+#             */
/*   Updated: 2020/10/05 05:18:36 by dthan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static char			*prompt_heredoc(char *end_word)
{
	t_l				l;

	ft_memset(&l, 0, sizeof(t_l));
	l.type = LINE_TYPE_HEREDOC;
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
		l.line = ft_strjoin_and_free_string2(l.line, prompt_heredoc(end_word));
	}
	return (l.line);
}

static void			apply_heredoc(t_astnode *here_end, t_list **heredoc)
{
	char 	*current_heredoc;
	t_list	*node;

	current_heredoc = prompt_heredoc(here_end->data);
	node = ft_lstnew(current_heredoc, sizeof(char*));
	if (*heredoc == NULL)
		*heredoc = node;
	else
		ft_lstadd_tail(heredoc, node);
}

void				find_heredoc(t_astnode *ast, t_list **heredoc)
{
	if (ast->type == AST_complete_command)
		find_heredoc(ast->left, heredoc);
	else if (ast->type == AST_list || ast->type == AST_and_or || \
			ast->type == AST_pipe_sequence || ast->type == AST_cmd_suffix)
	{
		find_heredoc(ast->left, heredoc);
		find_heredoc(ast->right, heredoc);
	}
	else if (ast->type == AST_simple_command)
		find_heredoc(ast->right, heredoc);
	else if (ast->type == AST_io_redirect)
		find_heredoc(ast->left, heredoc);
	else if (ast->type == AST_io_here && ft_strequ(ast->data, "<<"))
		apply_heredoc(ast->left, heredoc);
}

void				clear_heredoc(t_list *heredoc)
{
	t_list *temp;

	while(heredoc)
	{
		temp = heredoc;
		heredoc = heredoc->next;
		free(temp->content);
		free(temp);
	}
}
