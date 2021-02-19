/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_job.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthan <dthan@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/15 16:46:13 by dthan             #+#    #+#             */
/*   Updated: 2021/02/15 16:50:24 by dthan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

t_job	*find_the_current_job(void)
{
	t_job	*j_ptr;
	t_job	*current_job;
	int		add;

	j_ptr = g_shell.first_job;
	current_job = NULL;
	add = 0;
	while (j_ptr)
	{
		if (job_is_stopped(j_ptr))
		{
			current_job = j_ptr;
			add = 1;
		}
		else if (!add)
			current_job = j_ptr;
		j_ptr = j_ptr->next;
	}
	return (current_job);
}

int		count_nb_suspended_job(void)
{
	int		ct;
	t_job	*j_ptr;

	j_ptr = g_shell.first_job;
	ct = 0;
	while (j_ptr)
	{
		if (job_is_stopped(j_ptr))
			ct++;
		j_ptr = j_ptr->next;
	}
	return (ct);
}

t_job	*find_the_last_job(void)
{
	t_job	*last_job;
	t_job	*j_ptr;
	t_job	*current_job;
	int		add;

	last_job = NULL;
	add = (count_nb_suspended_job() > 1) ? 1 : 0;
	current_job = find_the_current_job();
	j_ptr = g_shell.first_job;
	if (!j_ptr || !current_job)
		return (NULL);
	while (j_ptr)
	{
		if ((add && j_ptr != current_job && job_is_stopped(j_ptr)) ||
			(!add && j_ptr != current_job))
			last_job = j_ptr;
		j_ptr = j_ptr->next;
	}
	return (last_job);
}
