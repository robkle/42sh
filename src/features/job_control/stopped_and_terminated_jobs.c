/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stopped_and_terminated_jobs.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthan <dthan@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/02 02:37:24 by dthan             #+#    #+#             */
/*   Updated: 2021/03/10 20:51:11 by dthan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	mark_process_status_exit(t_process *p, int status)
{
	ft_putchar('\n');
	p->stopped = 1;
	g_shell.exit_status = 128 + WSTOPSIG(status);
}

void	mark_process_status_signal(t_process *p, int status)
{
	p->completed = 1;
	if (WIFEXITED(status))
		g_shell.exit_status = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
    {
		g_shell.exit_status = 128 + WTERMSIG(status);
		ft_printf("%s: %d\n", g_shell.sig_msgs[WTERMSIG(status) - 1],
			WTERMSIG(status));
    }
}

int		mark_process_status_helper(
	t_process *first_process, pid_t pid, int status)
{
	t_process *p_ptr;

	p_ptr = first_process;
	while (p_ptr)
	{
		if (p_ptr->pid == pid)
		{
			p_ptr->status = status;
			if (WIFSTOPPED(status))
				mark_process_status_exit(p_ptr, status);
			else
				mark_process_status_signal(p_ptr, status);
			return (0);
		}
		p_ptr = p_ptr->next;
	}
	return (1);
}

int		mark_process_status(t_job *j, pid_t pid, int status)
{
	t_job	*j_ptr;
	int		ret;

	if (pid > 0)
	{
		j_ptr = j;
		while (j_ptr)
		{
			ret = mark_process_status_helper(j_ptr->first_process, pid, status);
			if (ret == 0)
				return (0);
			j_ptr = j_ptr->next;
		}
	}
	return (1);
}
