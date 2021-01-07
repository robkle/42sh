/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lauch_process.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthan <dthan@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/05 03:14:55 by dthan             #+#    #+#             */
/*   Updated: 2021/01/08 00:27:42 by dthan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

/*
** Note from simple command expansion:
** When a simple command is executed, the shell performs
** the following expansions, assignments, and redirections
** from left to right
*/

static void dup_fd_channel(int oldfd, int newfd)
{
	if (oldfd != newfd)
	{
		dup2(oldfd, newfd);
		close(oldfd);
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

int is_builtin(char *cmd_name)
{
	if (ft_strequ(cmd_name, "exit") || \
		ft_strequ(cmd_name, "cd") || \
		ft_strequ(cmd_name, "pwd") || \
		ft_strequ(cmd_name, "env") || \
		ft_strequ(cmd_name, "setenv") || \
		ft_strequ(cmd_name, "unsetenv") || \
		ft_strequ(cmd_name, "jobs") || \
		ft_strequ(cmd_name, "fg") || \
		ft_strequ(cmd_name, "bg") || \
		ft_strequ(cmd_name, "echo"))
		return (1);
	return (0);
}

int exec_builtin(t_process *p)
{
	if (ft_strequ(p->av[0], "exit"))
		ft_exit(EXIT_SUCCESS);
	else if (ft_strequ(p->av[0], "cd"))
		return (ft_cd(p));
	else if (ft_strequ(p->av[0], "pwd"))
		return (ft_pwd());
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
	// else if (ft_strequ(p->av[0], "type"))
	// 	return (ft_type(p));
	// else if (ft_strequ(p->av[0], "hash"))
	// 	return (ft_hash(p));
	else if (ft_strequ(p->av[0], "echo"))
		return (ft_echo(p));
	return (EXIT_FAILURE);
}

int lauch_process(t_process *p)
{
	if (is_builtin(p->av[0]))
		return (exec_builtin(p));
	else if (is_in_path(p))
		return (make_child_path(p));
	else if (possible_to_access_file(p))
		return (make_child_binary(p));
	else if (p->av[0][0] != '.' && p->av[0][0] != '/')
		ft_dprintf(2, "%s: %s: command not found\n", SHELL_NAME, p->av[0]);
	return (127);
}

void lauch_in_child_process(t_job *j, t_process *p)
{
	(j->pipe_fd_closer[0]) ? close(j->pipe_fd_closer[0]) : 0;
	(j->pipe_fd_closer[1]) ? close(j->pipe_fd_closer[1]) : 0;
	//handle_expansions
	if (handle_expansion(p) == EXIT_FAILURE)
	 	exit(EXIT_FAILURE);
	//handle_assignments
	set_stdin_stdout_stderr_channels(p->stdin, p->stdout, p->stderr);
	if (handle_redirection(p) == EXIT_FAILURE)
		exit(EXIT_FAILURE);
	set_process_group_id(j, getpid());
	if (j->foreground)
		ft_tcsetpgrp(STDIN_FILENO, j->pgid);
	sig_controller(CHILD);
	exit(lauch_process(p));
}

int is_execute_on_parent_process(int foreground, char *cmd_name)
{
	if (!foreground)
		return (0);
	// if (ft_strequ(cmd_name, "exit") || 
	// 	ft_strequ(cmd_name, "alias") || 
	// 	ft_strequ(cmd_name, "unalias") || 
	// 	ft_strequ(cmd_name, "cd") || 
	// 	ft_strequ(cmd_name, "setenv") || 
	// 	ft_strequ(cmd_name, "unsetenv") || 
	// 	ft_strequ(cmd_name, "jobs") || 
	// 	ft_strequ(cmd_name, "fg") || 
	// 	ft_strequ(cmd_name, "bg") || 
	// 	ft_strequ(cmd_name, "fc"))
	// 	return (1);
	if (ft_strequ(cmd_name, "exit") ||
		ft_strequ(cmd_name, "alias") ||
		ft_strequ(cmd_name, "unalias") ||
		ft_strequ(cmd_name, "cd") ||
		ft_strequ(cmd_name, "setenv") ||
		ft_strequ(cmd_name, "unsetenv") ||
		ft_strequ(cmd_name, "jobs") ||
		ft_strequ(cmd_name, "fg") ||
		ft_strequ(cmd_name, "bg") ||
		ft_strequ(cmd_name, "fc"))
		return (1);
	return (0);
}

int lauch_process_which_can_change_shell(t_process *p)
{
	if (ft_strequ(p->av[0], "exit"))
		return (ft_exit(EXIT_SUCCESS));
	else if (ft_strequ(p->av[0], "alias"))
		return (ft_alias(p));
	else if (ft_strequ(p->av[0], "unalias"))
		return (ft_unalias(p));
	else if (ft_strequ(p->av[0], "cd"))
		return (ft_cd(p));
	else if (ft_strequ(p->av[0], "setenv"))
		return (ft_setenv(p));
	else if (ft_strequ(p->av[0], "unsetenv"))
		return (ft_unsetenv(p));
	else if (ft_strequ(p->av[0], "fg"))
		return (ft_fg(p));
	else if (ft_strequ(p->av[0], "bg"))
		return (ft_bg(p));
	else if (ft_strequ(p->av[0], "jobs"))
		return (ft_jobs(p));
	else if (ft_strequ(p->av[0], "fc"))
		return (ft_fc(p));
	return (EXIT_FAILURE);
}

static void reset_stdin_stdout_stderr_channels(t_process *p, int std[3])
{
	if (p->stdin != 0)
	{
		dup2(std[SAVED_STDIN], STDIN_FILENO);
		close(std[STDIN_FILENO]);
	}
	if (p->stdout != 1)
	{
		dup2(std[SAVED_STDIN], STDOUT_FILENO);
		close(std[STDOUT_FILENO]);
	}
	if (p->stderr != 2)
	{
		dup2(std[SAVED_STDIN], STDERR_FILENO);
		close(std[STDERR_FILENO]);
	}
}

int lauch_in_parent_process(t_process *p)
{
	int std[3];
	int ret;

	(p->stdin != 0) ? std[SAVED_STDIN] = dup(STDIN_FILENO) : 0;
	(p->stdout != 1) ? std[SAVED_STDOUT] = dup(STDOUT_FILENO) : 0;
	(p->stderr != 2) ? std[SAVED_STDERR] = dup(STDERR_FILENO) : 0;
	if (handle_expansion(p) == EXIT_FAILURE)
	 	return(EXIT_FAILURE);
	if (handle_redirection(p) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	set_stdin_stdout_stderr_channels(p->stdin, p->stdout, p->stderr);
	ret = lauch_process_which_can_change_shell(p);
	reset_stdin_stdout_stderr_channels(p, std);
	return (ret);
}

void fork_and_lauch_in_child_process(t_job* j, t_process *p)
{
	pid_t pid;

	pid = fork();
	if (pid == 0)
		lauch_in_child_process(j, p);
	else if (pid < 0)
	{
		ft_putstr_fd("Fork Failed\n" ,2);
		exit(EXIT_FAILURE);
	}
	p->pid = pid;
	set_process_group_id(j, pid);
}

void	lauch_simple_command(t_job *j, t_process *p)
{	
	if (is_execute_on_parent_process(j->foreground, p->av[0]))
	{
		p->status = lauch_in_parent_process(p);
		p->completed = COMPLETED;
	}
	else
		fork_and_lauch_in_child_process(j, p);
}
