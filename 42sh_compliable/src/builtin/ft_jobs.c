/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_jobs.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthan <dthan@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/02 04:00:07 by dthan             #+#    #+#             */
/*   Updated: 2020/10/06 17:22:02 by dthan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int ft_jobs(void)
{
	t_list *j_ptr;
	t_job *j;
	int i;

	i = 1;
	j_ptr = g_shell.first_job;
	while (j_ptr)
	{
		j = (t_job*)j_ptr->content;
		ft_printf("[%d]  +  %d  %s  %s\n", \
					i++, \
					j->pgid, \
					job_is_stopped(j) ? "suspended" : "running", \
					j->command);
		j_ptr = j_ptr->next; 
	}
	return (EXIT_SUCCESS);
}
