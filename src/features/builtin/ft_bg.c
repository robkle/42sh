/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bg.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthan <dthan@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/13 13:05:50 by dthan             #+#    #+#             */
/*   Updated: 2020/12/18 18:12:52 by dthan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void change_running_state(t_job *j)
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

int continue_the_suspended_job(t_job *j)
{
	ft_printf("[%d] %s &\n", j->id, j->command);
	put_job_in_background(j, 1);
	change_running_state(j);
	j->foreground = 0;
	j->notified = 0;
	return (EXIT_SUCCESS);
}

int ft_bg_middle_man(t_job *j)
{
	if (j != NULL)
	{
		if (job_is_stopped(j))
			return (continue_the_suspended_job(j));
		update_status();
		if (job_is_completed(j))
			ft_dprintf(2, "%s: bg: job has terminated\n", SHELL_NAME);
		else
			ft_dprintf(2, "%s: bg: job %d already in background\n", SHELL_NAME, j->id);
		return (EXIT_FAILURE);
	}
	if ((j = find_the_current_job()) != NULL)
	{
		if (job_is_stopped(j))
			return (continue_the_suspended_job(j));
		update_status();
		if (job_is_completed(j))
			ft_dprintf(2, "%s: bg: job has terminated\n", SHELL_NAME);
		else
			ft_dprintf(2, "%s: bg: job %d already in background\n", SHELL_NAME, j->id);
		return (EXIT_FAILURE);
	}
	ft_dprintf(2, "%s: bg: current: no such job\n", SHELL_NAME);
	return (EXIT_FAILURE);
}

int	ft_bg(t_process *p)
{
	t_job *j;
	
	j = NULL;
	if (p->av[1] == NULL || ft_strequ(p->av[1], "%"))
		return (ft_bg_middle_man(j));
	else if ((j = is_valid_job_id(p->av[1])) != NULL)
		return (ft_bg_middle_man(j));
	ft_dprintf(2, "%s: bg: %s: no such job\n", SHELL_NAME, p->av[1]);
	return (EXIT_FAILURE);
}

int ft_bg_child()
{
	ft_dprintf(2, "%s: bg: no job control\n", SHELL_NAME);
	return (EXIT_FAILURE);
}
