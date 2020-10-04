/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stopped_and_terminated_jobs.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthan <dthan@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/02 02:37:24 by dthan             #+#    #+#             */
/*   Updated: 2020/10/04 03:34:52 by dthan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/shell.h"
#include <errno.h> //using errno here need to check

int job_is_stopped(t_job *j)
{
	t_process *p;
	t_list *p_ptr;

	p_ptr = j->process;
	while(p_ptr)
	{
		p = (t_process*)(p_ptr->content);
		if (!p->completed && !p->stopped)
			return (0);
	}
	return (1);
}

int job_is_completed(t_job *j)
{
	t_process *p;
	t_list *p_ptr;

	p_ptr = j->process;
	while(p_ptr)
	{
		p = (t_process*)(p_ptr->content);
		if (!p->completed)
			return (0);
	}
	return (1);
}

/* Store the status of the process pid that was returned by waitpid*/
int mark_process_status(pid_t pid, int status)
{
	t_list *j_ptr;
	// t_job	*j;
	t_list *p_ptr;
	t_process *p;

	if (pid > 0)
	{
		/* Update the record for the process. */
		j_ptr = g_shell.job;
		while (j_ptr)
		{
			p_ptr = ((t_job*)(j_ptr->content))->process;
			while (p_ptr)
			{
				p = (t_process*)(p_ptr->content);
				if (p->pid == pid)
				{
					p->status = status;
					if (WIFSTOPPED(status))
						p->stopped = 1;
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

/* Check for processes that have status information available, without blocking*/
void update_status(void)
{
	int status;
	pid_t pid;

	pid = waitpid(WAIT_ANY, &status, WUNTRACED | WNOHANG);
	while (!mark_process_status(pid, status))
		pid = waitpid(WAIT_ANY, &status, WUNTRACED | WNOHANG);
}

/* Check for processes that have status information available,
blocking until all processes in teh given job have reported*/
void wait_for_job(t_job *j)
{
	int status = 10;
	int pid;
	t_process *p;

	p = (t_process*)(j->process->content);
	ft_printf("cpid: %d\n", j->pgid);
	ft_printf("cpid2: %d\n", p->pid);
	pid = waitpid(p->pid, &status, WUNTRACED);
	ft_printf("cpid3: %d\n", pid);
	if (pid == -1)
	{
		perror("waitpid");
		exit(EXIT_FAILURE);
	}
	// while(1)
	// {
	// 	if ((pid = waitpid(-j->pgid, &status, WUNTRACED)) == -1 && errno != ECHILD)
	// 	{
	// 		perror("waitpid");
	// 	}
	// 	if (pid <= 1 || mark_process_status(pid, status) || job_is_stopped(j) || job_is_completed(j))
	// 		break;
	// }
}

/* Format information about job status for the user to look at */
void format_job_info(t_list *j, const char *status)
{
	ft_printf("%d (%s): %s\n", ((t_job*)(j->content))->pgid,
								status,
								((t_job*)(j->content))->command);
}

/* Notify the user about stopped or terminated jobs.
	Delete terminated jobs from the active job list.*/
void	do_job_notification(void)
{
	t_list *j;
	t_list *jlast;
	t_list *jnext;
	
	/* Updated status information for child processes */
	update_status();
	jlast = NULL;
	j = g_shell.job;
	while (j)
	{
		jnext = j->next;
		/* If all processes have completed, tell the user the job has 
		completed and delete it from the list of active jobs*/
		if (job_is_completed((t_job*)(j->content)))
		{
			format_job_info(j, "completed");
			if (jlast)
				jlast->next = jnext;
			else
				g_shell.job = jnext;
			delete_job(j);
		}
		else if (job_is_stopped((t_job*)(j->content)) && !((t_job*)(j->content))->notified)
		{
			format_job_info(j, "stopped");
			((t_job*)(j->content))->notified = 1;
			jlast = j;
		}
		else /*Dont say anything about jobs that are still running*/
			jlast = j;
		j = jnext;
	}
}
