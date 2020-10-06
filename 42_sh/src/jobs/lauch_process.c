/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lauch_process.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthan <dthan@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/05 03:14:55 by dthan             #+#    #+#             */
/*   Updated: 2020/10/06 17:05:37 by dthan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/shell.h"

static void dup_fd_channel(int fd, int std_fd)
{
	if (fd != std_fd)
	{
		dup2(fd, std_fd);
		close(fd);
	}
}

static void set_stdin_stdout_stderr_channels(int infd, int outfd, int errfd)
{
	dup_fd_channel(infd, STDIN_FILENO);
	dup_fd_channel(outfd, STDOUT_FILENO);
	dup_fd_channel(errfd, STDERR_FILENO);
}

static void set_process_group_id(t_job *j, pid_t pid)
{
	if (j->pgid == 0)
		j->pgid = pid;
	setpgid(pid, j->pgid);
}

void lauch_child_process(t_job *j, t_process *p)
{
	char	*path;

	path = NULL;
	handle_redirect(p->redi, p);
	set_process_group_id(j, getpid());
	if (j->foreground)
		ft_tcsetpgrp(STDIN_FILENO, j->pgid);
	sig_controller(CHILD);
	set_stdin_stdout_stderr_channels(p->stdin, p->stdout, p->stderr);
	/* NOTE: Very not sure about this part */
	if (is_builtin_printing(p->av[0]))
		builtins_printing(p);
	else if ((path = is_in_path(p)))
		// return (make_child_path(c, path));
		make_child_path(p, path); //return sth here, but why need to return?
	else if (possible_to_access_file(p))
		make_child_binary(p);
	else if (p->av[0][0] != '.' && p->av[0][0] != '/')
		error_monitor(p->av[0], ": command not found", NULL, EXIT_FAILURE);
	ft_exit(EXIT_FAILURE);
}

int		lauch_process(t_job *j, t_process *p)
{
	pid_t	cpid;
	
	if (is_builtin_not_printing(p->av[0]))
		return (builtins_not_printing(p));
	if ((cpid = fork()) == 0)
		lauch_child_process(j, p);
	else if (cpid < 0)
	{
		perror("fork"); // manage error here
		exit(EXIT_FAILURE);
	}
	p->pid = cpid;
	set_process_group_id(j, cpid);
	return (UNAVAILABLE_STATUS);
}
