/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bg.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthan <dthan@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/13 13:05:50 by dthan             #+#    #+#             */
/*   Updated: 2020/10/16 15:22:49 by dthan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

t_job *find_the_most_recently_suspended_job(void)
{
	t_list *j_ptr;
	t_job *the_most_recently_suspended_j;

	if (g_shell.first_job == NULL)
		return (NULL);
	j_ptr = g_shell.first_job;
	the_most_recently_suspended_j = NULL;
	while (j_ptr)
	{
		if (job_is_stopped((t_job*)(j_ptr->content)))
			the_most_recently_suspended_j = (t_job*)(j_ptr->content);
		j_ptr = j_ptr->next;
	}
	return (the_most_recently_suspended_j);
}

void change_running_state(t_job *j)
{
	t_list *p_ptr;
	t_process *p;

	p_ptr = j->first_process;
	while (p_ptr)
	{
		p = (t_process*)(p_ptr->content);
		if (p->stopped)
			p->stopped = 0;
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

int ft_bg_middle_man(int job_id)
{
	t_job *j;

	if (job_id == -1)
	{
		if ((j = find_the_most_recently_suspended_job()) != NULL)
			return (continue_the_suspended_job(j));
		ft_dprintf(2, "%s: bg: current: no such job\n", SHELL_NAME);
	}
	else
	{
		if ((j = find_job_with_id(job_id)) != NULL)
		{
			if (job_is_stopped(j))
				return (continue_the_suspended_job(j));
			else
				ft_dprintf(2, "%s: bg: job %d already in background\n", \
					SHELL_NAME, job_id);
		}
		else
			ft_dprintf(2, "%s: bg: %d: no such job\n", SHELL_NAME, job_id);
	}
	return (EXIT_FAILURE);
}

int	ft_bg(t_job *j, t_process *p)
{
	int job_id;

	if (p->av[1] == NULL || ft_strequ(p->av[1], "%"))
		return (ft_bg_middle_man(-1));
	else if ((job_id = is_valid_job_id(j, p->av[1])) != 0)
		return (ft_bg_middle_man(job_id));
	ft_dprintf(2, "%s: bg: %s: no such job\n", SHELL_NAME, p->av[1]);
	return (EXIT_FAILURE);
}