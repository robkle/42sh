/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stopped_and_terminated_jobs.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthan <dthan@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/02 02:37:24 by dthan             #+#    #+#             */
/*   Updated: 2021/01/08 01:26:30 by dthan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include <errno.h> //using errno here need to check

int job_is_stopped(t_job *j)
{
	t_process *p_ptr;

	p_ptr = j->first_process;
	while(p_ptr)
	{
		if (!p_ptr->completed && !p_ptr->stopped)
			return (0);
		p_ptr = p_ptr->next;
	}
	return (1);
}

int job_is_completed(t_job *j)
{
	t_process *p_ptr;

	p_ptr = j->first_process;
	while(p_ptr)
	{
		if (!p_ptr->completed)
			return (0);
		p_ptr = p_ptr->next;
	}
	return (1);
}

int mark_process_status_helper(t_process *first_process, pid_t pid, int status)
{
	t_process *p_ptr;

	p_ptr = first_process;
	while (p_ptr) {
		if (p_ptr->pid == pid)
		{
			p_ptr->status = status;
			if (WIFSTOPPED(status))
			{
				ft_putchar('\n');
				p_ptr->stopped = 1;
				g_shell.exit_status = 128 + WSTOPSIG(status);
			}
			else
			{
				p_ptr->completed = 1;
				if (WIFEXITED(status))
					g_shell.exit_status = WEXITSTATUS(status);
				else if (WIFSIGNALED(status)) //here will be signal controller
					g_shell.exit_status = 128 + WTERMSIG(status);
			}
			return (0);
		}
		p_ptr = p_ptr->next;
	}
	return (1);
}

int mark_process_status(t_job *j, pid_t pid, int status)
{
	t_job *j_ptr;
	int ret;

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

void update_status(void)
{
	int status;
	pid_t pid;

	pid = waitpid(WAIT_ANY, &status, WUNTRACED | WNOHANG);
	while (!mark_process_status(g_shell.first_job, pid, status))
		pid = waitpid(WAIT_ANY, &status, WUNTRACED | WNOHANG);
}

// void wait_for_job(t_job *j, int opt)
// {
// 	int pid;
// 	int status;

// 	pid = waitpid(-j->pgid, &status, opt);
// 	while(!mark_process_status(j, pid, status) && !job_is_stopped(j) &&!job_is_completed(j))
// 		pid = waitpid(-j->pgid, &status, opt);
// }

void wait_for_job(t_job *j, int opt)
{
	int status;
	t_process *p_ptr;

	p_ptr = j->first_process;
	while (!job_is_stopped(j) && !job_is_completed(j))
	{
		while (p_ptr)
		{
			waitpid(p_ptr->pid, &status, opt);
			mark_process_status(j, p_ptr->pid, status);
			p_ptr = p_ptr->next;
		}
	}
}

void format_job_info(t_job *j, const char *status, int opt)
{
	ft_printf("[%d]", j->id);
	if (is_the_current_job(j))
		ft_printf("%-3c", '+');
	else if (is_the_last_job(j))
		ft_printf("%-3c", '-');
	else
		ft_putstr("   ");
	ft_printf("%-24s%s", status, j->command);
	if (opt)
		(!j->foreground) ? ft_putstr(" &") : 0;
	ft_putchar('\n');
}

void	do_job_notification(void)
{
	t_job *j;
	t_job *jlast;
	t_job *jnext;
	
	/* Updated status information for child processes */
	if (g_shell.first_job == NULL)
		return ;
	update_status();
	jlast = NULL;
	j = g_shell.first_job;
	while (j)
	{
		jnext = j->next;
		if (job_is_completed(j))
		{
			(!j->foreground) ? format_job_info(j, "Done", 0) : 0;
			if (jlast)
				jlast->next = jnext;
			else
				g_shell.first_job = jnext;
			delete_job(j, 0);
		}
		else if (job_is_stopped(j) && !j->notified)
		{
			format_job_info(j, "Stopped(SIGTSTP)", 0);
			j->notified = 1;
			jlast = j;
		}
		else
			jlast = j;
		j = jnext;
	}
}
