/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_list.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthan <dthan@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/16 08:35:21 by dthan             #+#    #+#             */
/*   Updated: 2020/10/16 16:04:00 by dthan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

// void		execute_list(t_astnode *ast, t_list **heredoc, t_list *first_job)
// {
// 	t_list *next_job;

// 	next_job = NULL;
// 	if (ast->type == AST_list)
// 	{
// 		next_job = create_job();
// 		put_to_list_job(next_job);
// 		if (ft_strequ(ast->data, "&"))
// 			((t_job*)(next_job->content))->foreground = 0;
// 		execute_and_or(ast->left, heredoc, (t_job*)(first_job->content));
// 		if (((t_job*)(first_job->content))->foreground == 0)
// 		{
// 			job_command_builder(1, (t_job*)(first_job->content), " &");
// 			print_job_background(first_job);
// 		}
// 		execute_list(ast->right, heredoc, next_job);
// 	}
// 	else
// 	{
// 		execute_and_or(ast, heredoc, (t_job*)(first_job->content));
// 		if (((t_job*)(first_job->content))->foreground == 0)
// 		{
// 			job_command_builder(1, (t_job*)(first_job->content), " &");
// 			print_job_background(first_job);
// 		}
// 	}
// }

void		execute_list(t_astnode *ast, int foreground)
{
	if (ast->type == AST_list)
	{
		if (ft_strequ(ast->data, "&"))
			execute_list(ast->left, 0);
		else
			execute_list(ast->left, 1);
		if (!foreground && ast->right->type == AST_and_or)
			execute_and_or_bg(ast->right);
		else
			execute_and_or(ast->right, foreground, 0, 1);
	}
	else if (!foreground && ast->type == AST_and_or)
		execute_and_or_bg(ast);
	else
		execute_and_or(ast, foreground, 0, 1);
}
