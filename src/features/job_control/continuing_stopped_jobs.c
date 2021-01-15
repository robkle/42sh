/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   continuing_stopped_jobs.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthan <dthan@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/02 03:39:32 by dthan             #+#    #+#             */
/*   Updated: 2020/12/18 18:19:06 by dthan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

/* Mark a stopped job J as being running again */

void mark_job_as_running(t_job *j)
{
	t_process *p_ptr;
	
	p_ptr = j->first_process;
	while(p_ptr)
	{
		p_ptr->stopped = 0;
		p_ptr = p_ptr->next;
	}
	j->notified = 0;
}

/* Continue the job j */

// void continue_job(t_job *j, int foreground)
// {
// 	mark_job_as_running(j);
// 	if (foreground)
// 		put_job_in_foreground(j, 1);
// 	else
// 		put_job_in_background(j , 1);
// }
