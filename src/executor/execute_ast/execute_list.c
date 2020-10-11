/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_list.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthan <dthan@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/16 08:35:21 by dthan             #+#    #+#             */
/*   Updated: 2020/10/08 03:38:18 by dthan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void		execute_list(t_astnode *ast, t_list **heredoc, t_list *first_job)
{
	t_list *next_job;

	next_job = NULL;
	if (ast->type == AST_list)
	{
		next_job = create_job();
		put_to_list_job(next_job);
		if (ft_strequ(ast->data, "&"))
			((t_job*)(next_job->content))->foreground = 0;
		execute_and_or(ast->left, heredoc, (t_job*)(first_job->content));
		g_shell.previous_exitcode = EXIT_SUCCESS;
		execute_list(ast->right, heredoc, next_job);
	}
	else
		execute_and_or(ast, heredoc, (t_job*)(first_job->content));
}
