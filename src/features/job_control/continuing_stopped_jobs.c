/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   continuing_stopped_jobs.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthan <dthan@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/02 03:39:32 by dthan             #+#    #+#             */
/*   Updated: 2021/01/28 17:23:43 by dthan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

/*
** Mark a stopped job J as being running again
*/

void	change_running_state(t_job *j)
{
	t_process *p_ptr;

	p_ptr = j->first_process;
	while (p_ptr)
	{
		if (p_ptr->stopped)
			p_ptr->stopped = 0;
		p_ptr = p_ptr->next;
	}
}

int		continue_the_suspended_job(t_job *j)
{
	ft_printf("[%d] %s &\n", j->id, j->command);
	put_job_in_background(j, 1);
	change_running_state(j);
	j->foreground = 0;
	j->notified = 0;
	return (EXIT_SUCCESS);
}
