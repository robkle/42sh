/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lauch_process_child_shell.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihwang <ihwang@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/28 03:49:29 by dthan             #+#    #+#             */
/*   Updated: 2021/02/02 22:47:14 by ihwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static int	is_builtin(char *cmd_name)
{
	if (ft_strequ(cmd_name, "exit") ||
		ft_strequ(cmd_name, "cd") ||
		ft_strequ(cmd_name, "pwd") ||
		ft_strequ(cmd_name, "env") ||
		ft_strequ(cmd_name, "setenv") ||
		ft_strequ(cmd_name, "unsetenv") ||
		ft_strequ(cmd_name, "jobs") ||
		ft_strequ(cmd_name, "fg") ||
		ft_strequ(cmd_name, "bg") ||
		ft_strequ(cmd_name, "echo") ||
		ft_strequ(cmd_name, "set") ||
		ft_strequ(cmd_name, "unset") ||
		ft_strequ(cmd_name, "hash"))
		return (1);
	return (0);
}

static int	exec_builtin2(t_process *p)
{
	if (ft_strequ(p->av[0], "echo"))
		return (ft_echo(p));
	// else if (ft_strequ(p->av[0], "type"))
	// 	return (ft_type(p));
	else if (ft_strequ(p->av[0], "set"))
		return (ft_set());
	else if (ft_strequ(p->av[0], "unset"))
		return (ft_unset(p->ac, p->av));
	else if (ft_strequ(p->av[0], "hash"))
		return (ft_hash(p));
	return (EXIT_FAILURE);
}

static int	exec_builtin(t_process *p)
{
	if (ft_strequ(p->av[0], "exit"))
		ft_exit(EXIT_SUCCESS);
	else if (ft_strequ(p->av[0], "cd"))
		return (ft_cd(p));
	else if (ft_strequ(p->av[0], "pwd"))
		return (ft_pwd(p));
	else if (ft_strequ(p->av[0], "env"))
		return (ft_env());
	else if (ft_strequ(p->av[0], "setenv"))
		return (ft_setenv(p));
	else if (ft_strequ(p->av[0], "unsetenv"))
		return (ft_unsetenv(p));
	else if (ft_strequ(p->av[0], "jobs"))
		return (ft_jobs_child(p));
	else if (ft_strequ(p->av[0], "fg"))
		return (ft_fg_child());
	else if (ft_strequ(p->av[0], "bg"))
		return (ft_bg_child());
	return (exec_builtin2(p));
}

static int	lauch_process(t_process *p, char *path)
{
	if (ft_strchr(p->av[0], '/') != NULL && possible_to_access_file(p))
		return (make_child_binary(p));
	else if (is_builtin(p->av[0]))
		return (exec_builtin(p));
	else if (path != NULL)
		return (make_child_path_sub(p, path));
	//else if (is_in_path(p))
	//	return (make_child_path(p));
	//else if (possible_to_access_file(p))
	//	return (make_child_binary(p));
	else if (p->av[0][0] != '.' && p->av[0][0] != '/')
		ft_dprintf(2, "%s: %s: command not found\n", SHELL_NAME, p->av[0]);
	return (127);
}

static void	set_process_group_id(t_job *j, pid_t pid)
{
	if (j->pgid == 0)
		j->pgid = pid;
	setpgid(pid, j->pgid);
}

static void	lauch_in_child_process(t_job *j, t_process *p, char *path)
{
	int old[3];

	old[0] = p->stdin;
	old[1] = p->stdout;
	old[2] = p->stderr;
	(j->pipe_fd_closer[0]) ? close(j->pipe_fd_closer[0]) : 0;
	(j->pipe_fd_closer[1]) ? close(j->pipe_fd_closer[1]) : 0;
	set_reset_stdin_stdout_stderr_channels(old);
	if (handle_redirection(p) == EXIT_FAILURE)
		exit(EXIT_FAILURE);
	set_process_group_id(j, getpid());
	if (j->foreground)
		ft_tcsetpgrp(STDIN_FILENO, j->pgid);
	sig_controller(CHILD);
	exit(lauch_process(p, path));
}

void	fork_and_launch_in_child_process(t_job *j, t_process *p, char *path)
{
	pid_t pid;

	pid = fork();
	if (pid == 0)
		lauch_in_child_process(j, p, path);
	else if (pid < 0)
	{
		ft_putstr_fd("Fork failed at laching child process\n", 2);
		exit(EXIT_FAILURE);
	}
	p->pid = pid;
	set_process_group_id(j, pid);
}
