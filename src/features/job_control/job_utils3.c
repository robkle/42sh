/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   job_utils3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihwang <ihwang@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/30 20:56:23 by ihwang            #+#    #+#             */
/*   Updated: 2021/03/30 20:57:03 by ihwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	set_job_complete_because_of_signal(t_job *j)
{
	t_process *p_ptr;

	p_ptr = j->first_process;
	while (p_ptr)
	{
		if (!p_ptr->completed)
		{
			kill(p_ptr->pid, SIGTERM);
			p_ptr->completed = 1;
		}
		p_ptr = p_ptr->next;
	}
}
