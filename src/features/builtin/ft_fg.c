/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fg.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthan <dthan@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/18 18:13:55 by dthan             #+#    #+#             */
/*   Updated: 2021/03/12 22:59:17 by dthan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int	wake_bg_job_up(t_job *j)
{
	update_status();
	if (job_is_completed(j))
	{
		ft_printf("%s: fg: job has terminated\n", SHELL_NAME);
		return (EXIT_FAILURE);
	}
	ft_printf("%s\n", j->command);
	if (job_is_stopped(j))
		put_job_in_foreground(j, 1);
	else
		put_job_in_foreground(j, 0);
	j->foreground = 1;
	return (EXIT_SUCCESS);
}

int	ft_fg_middle_man(t_job *job)
{
	if (job != NULL)
		return (wake_bg_job_up(job));
	job = find_the_current_job();
	if (job != NULL)
		return (wake_bg_job_up(job));
	ft_printf("%s: fg: current: no such job\n", SHELL_NAME);
	return (EXIT_FAILURE);
}

int	ft_fg(t_process *p)
{
	t_job *job;

	job = NULL;
	if (p->av[1] == NULL || ft_strequ(p->av[1], "%"))
		return (ft_fg_middle_man(job));
	else if ((job = is_valid_job_id(p->av[1])) != NULL)
		return (ft_fg_middle_man(job));
	ft_dprintf(2, "%s: fg: %s: no such job\n", SHELL_NAME, p->av[1]);
	return (EXIT_FAILURE);
}

int	ft_fg_child(void)
{
	ft_dprintf(2, "%s: fg: no job control\n", SHELL_NAME);
	return (EXIT_FAILURE);
}
