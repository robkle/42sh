/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stopped_and_terminated_jobs.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthan <dthan@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/02 02:37:24 by dthan             #+#    #+#             */
/*   Updated: 2020/10/14 13:24:47 by dthan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/shell.h"
#include <errno.h> //using errno here need to check

int job_is_stopped(t_job *j)
{
	t_process *p;
	t_list *p_ptr;

	p_ptr = j->first_process;
	while(p_ptr)
	{
		p = (t_process*)(p_ptr->content);
		if (!p->completed && !p->stopped)
			return (0);
		p_ptr = p_ptr->next;
	}
	return (1);
}

int job_is_completed(t_job *j)
{
	t_process *p;
	t_list *p_ptr;

	p_ptr = j->first_process;
	while(p_ptr)
	{
		p = (t_process*)(p_ptr->content);
		if (!p->completed)
			return (0);
		p_ptr = p_ptr->next;
	}
	return (1);
}

int mark_process_status(pid_t pid, int status)
{
	t_list *j_ptr;
	t_list *p_ptr;
	t_process *p;

	if (pid > 0)
	{
		/* Update the record for the process. */
		j_ptr = g_shell.first_job;
		while (j_ptr)
		{
			p_ptr = ((t_job*)(j_ptr->content))->first_process;
			while (p_ptr)
			{
				p = (t_process*)(p_ptr->content);
				if (p->pid == pid)
				{
					p->status = status;
					if (WIFSTOPPED(status))
					{
						ft_putchar('\n');
						p->stopped = 1;
					}
					else
					{
						p->completed = 1;
						if (WIFSIGNALED(status))
							ft_printf("%d: Terminated by signal %d.\n", (int)pid, WTERMSIG(p->status));
					}
					return (0);
				}
				p_ptr = p_ptr->next;
			}
			j_ptr = j_ptr->next;
		}	
		ft_printf("No child process %d.\n", pid); // need to change to stderr
		return (-1);
	}
	else if (pid == 0 || errno == ECHILD)
	{
		/* No processes ready to report */
		return (-1);
	}
	else
	{
		/* Other weird errors */
		perror("waitpid");
		return (-1); //-1 might be change to 1
	}
}

void update_status(void)
{
	int status;
	pid_t pid;

	pid = waitpid(WAIT_ANY, &status, WUNTRACED | WNOHANG);
	while (!mark_process_status(pid, status))
		pid = waitpid(WAIT_ANY, &status, WUNTRACED | WNOHANG);
}

void wait_for_job(t_job *j, int opt)
{
	int pid;
	int status;

	pid = waitpid(-j->pgid, &status, opt);
	while(!mark_process_status(pid, status) && !job_is_stopped(j) &&!job_is_completed(j))
		pid = waitpid(-j->pgid, &status, opt);
}

void format_job_info(t_job *j, int opt, const char *status)
{
	if ((opt == COMPLETED_JOB && !j->foreground) || opt == SUSPENDED_JOB)
		ft_printf("[%d]  %-20s%s\n", j->id, status, j->command);
}

void	do_job_notification(void)
{
	t_list *j;
	t_list *jlast;
	t_list *jnext;
	
	/* Updated status information for child processes */
	update_status();
	jlast = NULL;
	j = g_shell.first_job;
	while (j)
	{
		jnext = j->next;
		if (job_is_completed((t_job*)(j->content)))
		{
			format_job_info((t_job*)(j->content), 1, "Done");
			if (jlast)
				jlast->next = jnext;
			else
				g_shell.first_job = jnext;
			delete_job(j);
		}
		else if (job_is_stopped((t_job*)(j->content)) && !((t_job*)(j->content))->notified)
		{
			format_job_info((t_job*)(j->content), 2, "Stopped(SIGTSTP)");
			((t_job*)(j->content))->notified = 1;
			jlast = j;
		}
		else
			jlast = j;
		j = jnext;
	}
}
