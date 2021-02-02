/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_delete_job_tools.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthan <dthan@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/28 17:26:08 by dthan             #+#    #+#             */
/*   Updated: 2021/01/28 17:31:09 by dthan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void		delete_job(t_job *j, char option)
{
	if (option && job_is_stopped(j) && !job_is_completed(j))
	{
		if (kill(-j->pgid, SIGCONT) < 0)
			ft_dprintf(2, "kill (SIGCONT) error at delete job\n");
		kill(-j->pgid, SIGTERM);
	}
	delete_process(j);
	free(j->command);
	free(j);
}

void		delete_jobs(t_job *j_ptr, char option)
{
	t_job *temp_job;

	while (j_ptr)
	{
		temp_job = j_ptr;
		j_ptr = j_ptr->next;
		delete_job(temp_job, option);
	}
}

static int	get_job_id(void)
{
	int		id;
	t_job	*j_ptr;

	id = 1;
	j_ptr = g_shell.first_job;
	while (j_ptr)
	{
		if (id != j_ptr->id)
			break ;
		id++;
		j_ptr = j_ptr->next;
	}
	return (id);
}

t_job		*create_job(int foreground, int forked)
{
	t_job *j;

	j = ft_memalloc(sizeof(t_job));
	j->command = NULL;
	j->pgid = 0;
	j->notified = 0;
	tcgetattr(STDIN_FILENO, &j->term);
	j->first_process = NULL;
	j->stdin = STDIN_FILENO;
	j->stdout = STDOUT_FILENO;
	j->stderr = STDERR_FILENO;
	j->foreground = foreground;
	j->forked = forked;
	j->id = get_job_id();
	j->pipe_fd_closer[0] = 0;
	j->pipe_fd_closer[1] = 0;
	j->next = NULL;
	return (j);
}
