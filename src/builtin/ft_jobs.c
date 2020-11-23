/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_jobs.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthan <dthan@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/02 04:00:07 by dthan             #+#    #+#             */
/*   Updated: 2020/10/16 15:41:19 by dthan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void ft_jobs_printing_with_argv(t_job *j, char **argv)
{
	int i;
	int job_id;
	t_job *j_ptr;

	i = -1;
	while(argv[++i])
	{
		if ((job_id = is_valid_job_id(j ,argv[i])) == 0)
			ft_dprintf(2, "%s: jobs: %s: no such job\n", SHELL_NAME, argv[i]);
		else
		{
			j_ptr = find_job_with_id(job_id);
			if (!job_is_completed(j_ptr))
			{
				ft_printf("[%d]  +  %d  %s  %s", \
					j_ptr->id, \
					j_ptr->pgid, \
					job_is_stopped(j_ptr) ? "suspended" : "running", \
					j_ptr->command);
				(!j_ptr->foreground) ? ft_putstr(" &\n") : ft_putchar('\n');
			}
		}
	}
}

void ft_jobs_printing_without_argv(t_job *j)
{
	t_list *j_node;
	t_job *j_ptr;

	j_node = g_shell.first_job;
	while (j_node)
	{
		j_ptr = (t_job*)(j_node->content);
		if (!job_is_completed(j_ptr) && j_ptr != j)
		{
			ft_printf("[%d]  +  %d  %s  %s", \
					j_ptr->id, \
					j_ptr->pgid, \
					job_is_stopped(j_ptr) ? "suspended" : "running", \
					j_ptr->command);
			(!j_ptr->foreground) ? ft_putstr(" &\n") : ft_putchar('\n');
		}
		j_node = j_node->next;
	}
}

int ft_jobs(t_job *j, t_process *p)
{
	update_status();
	if (p->av[1])
		ft_jobs_printing_with_argv(j, &p->av[1]);
	else
		ft_jobs_printing_without_argv(j);
	return (EXIT_SUCCESS);
}
