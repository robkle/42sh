/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_list.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthan <dthan@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/16 08:35:21 by dthan             #+#    #+#             */
/*   Updated: 2020/10/05 05:56:45 by dthan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

// void	execute_list(t_astnode *ast, t_list **heredoc, t_list **first_job)
// {
// 	t_list *next_job;

// 	next_job = NULL;
// 	if (ast->type == AST_list)
// 	{
// 		next_job = create_job();
// 		if (ft_strequ(ast->data, "&"))
// 			((t_job*)(next_job->content))->foreground = 0;
// 		execute_and_or(ast->left, heredoc, first_job);
// 		if (((t_job*)((*first_job)->content))->foreground)
// 		{
// 			put_job_in_foreground((t_job*)((*first_job)->content), 0);
// 			put_to_list_job(*first_job);
// 			// put_to_list_job(*first_job);
// 		}
// 		else
// 		{
// 			put_job_in_background((t_job*)((*first_job)->content), 0);
// 			put_to_list_job(*first_job);
// 		}
// 		execute_list(ast->right, heredoc, &next_job);
// 		if (((t_job*)(next_job->content))->foreground)
// 		{
// 			put_job_in_foreground((t_job*)(next_job->content), 0);
// 			put_to_list_job(next_job);
// 			// put_to_list_job(next_job);
// 		}
// 		else
// 		{
// 			put_job_in_background((t_job*)(next_job->content), 0);
// 			put_to_list_job(next_job);
// 		}
// 	}
// 	else
// 	{
// 		execute_and_or(ast, heredoc, first_job);
// 		if (((t_job*)((*first_job)->content))->foreground)
// 		{
// 			put_job_in_foreground((t_job*)((*first_job)->content), 0);
// 			put_to_list_job(*first_job);
// 		}
// 		else
// 		{
// 			put_job_in_background((t_job*)((*first_job)->content), 0);
// 			put_to_list_job(*first_job);
// 		}
// 	}
// }

void	execute_list(t_astnode *ast, t_list **heredoc, t_list *first_job)
{
	t_list *next_job;

	next_job = NULL;
	if (ast->type == AST_list)
	{
		next_job = create_job();
		if (ft_strequ(ast->data, "&"))
			((t_job*)(next_job->content))->foreground = 0;
		execute_and_or(ast->left, heredoc, (t_job*)(first_job->content));
		if (((t_job*)(first_job->content))->foreground)
		{
			put_to_list_job(first_job);
			put_job_in_foreground((t_job*)(first_job->content), 0);
			
			// put_to_list_job(*first_job);
		}
		else
		{
			put_to_list_job(first_job);
			put_job_in_background((t_job*)(first_job->content), 0);
			
		}
		execute_list(ast->right, heredoc, next_job);
		if (((t_job*)(next_job->content))->foreground)
		{
			put_to_list_job(next_job);
			put_job_in_foreground((t_job*)(next_job->content), 0);
			
			// put_to_list_job(next_job);
		}
		else
		{
			put_to_list_job(next_job);
			put_job_in_background((t_job*)(next_job->content), 0);
			
		}
	}
	else
	{
		execute_and_or(ast, heredoc, (t_job*)(first_job->content));
		if (((t_job*)(first_job->content))->foreground)
		{
			put_to_list_job(first_job);
			put_job_in_foreground((t_job*)(first_job->content), 0);
			
		}
		else
		{
			put_to_list_job(first_job);
			put_job_in_background((t_job*)(first_job->content), 0);
		}
	}
}
