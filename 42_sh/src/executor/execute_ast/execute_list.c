/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_list.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthan <dthan@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/16 08:35:21 by dthan             #+#    #+#             */
/*   Updated: 2020/10/05 17:00:55 by dthan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static void	initialize_job_position(t_list *job)
{
	t_job *j_ptr;

	j_ptr = (t_job*)(job->content);
	if (j_ptr->foreground)
		put_job_in_foreground(j_ptr, 0);
	else
		put_job_in_background(j_ptr, 0);
}

void		execute_list(t_astnode *ast, t_list **heredoc, t_list *first_job)
{
	t_list *next_job;

	next_job = NULL;
	if (ast->type == AST_list)
	{
		next_job = create_job();
		if (ft_strequ(ast->data, "&"))
			((t_job*)(next_job->content))->foreground = 0;
		execute_and_or(ast->left, heredoc, (t_job*)(first_job->content));
		put_to_list_job(first_job);
		initialize_job_position(first_job);
		execute_list(ast->right, heredoc, next_job);
		put_to_list_job(next_job);
		initialize_job_position(next_job);
	}
	else
	{
		execute_and_or(ast, heredoc, (t_job*)(first_job->content));
		put_to_list_job(first_job);
		initialize_job_position(first_job);
	}
}
