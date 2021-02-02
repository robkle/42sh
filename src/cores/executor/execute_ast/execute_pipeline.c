/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_pipeline.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthan <dthan@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/16 08:36:24 by dthan             #+#    #+#             */
/*   Updated: 2021/01/28 02:40:37 by dthan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	initialize_job_position(t_job *j)
{
	if (j->foreground)
	{
		put_job_in_foreground(j, 0);
		if (!job_is_completed(j) && job_is_stopped(j))
			put_to_list_job(j);
	}
	else
	{
		put_job_in_background(j, 0);
		if (j->forked)
			wait_for_job(j, 0);
		else
		{
			put_to_list_job(j);
			ft_printf("[%d] %d\n", j->id, j->pgid);
		}
	}
}

int		execute_pipeline(t_astnode *ast, t_job *job)
{
	int ret;

	ret = UNAVAILABLE_STATUS;
	execute_pipe_sequence(ast, job);
	initialize_job_position(job);
	if (job_is_completed(job))
	{
		ret = last_process_status(job);
		delete_job(job, 0);
	}
	return (ret);
}
