/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lauch_process.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthan <dthan@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/05 03:14:55 by dthan             #+#    #+#             */
/*   Updated: 2020/11/03 11:29:56 by dthan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/shell.h"

/*
** Note from simple command expansion:
** When a simple command is executed, the shell performs
** the following expansions, assignments, and redirections
** from left to right
*/

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

int exec_builtin(t_job *j, t_process *p)
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
		return (ft_jobs(j, p));
	else if (ft_strequ(p->av[0], "fg"))
		return (ft_fg_child()); //special case for fg, maybe bg as well
	// else if (ft_strequ(p->av[0], "bg"))
	// 	return (ft_bg());
	// else if (ft_strequ(p->av[0], "type"))
	// 	return (ft_type(p));
	// else if (ft_strequ(p->av[0], "hash"))
	// 	return (ft_hash(p));
	else if (ft_strequ(p->av[0], "echo"))
		return (ft_echo(p));
	return (EXIT_FAILURE);
}

int lauch_process(t_job *j, t_process *p)
{
	if (is_builtin(p->av[0]))
		return (exec_builtin(j, p));
	else if (is_in_path(p))
		return (make_child_path(p));
	else if (possible_to_access_file(p))
		return (make_child_binary(p));
	else if (p->av[0][0] != '.' && p->av[0][0] != '/')
		ft_dprintf(STDERR_FILENO, "%s: %s: %s\n", \
			SHELL_NAME, p->av[0], SHELL_CMDNF);
	return (EXIT_FAILURE);
}

void lauch_in_child_process(t_job *j, t_process *p)
{
	//handle_expansions
	// if (handle_expansion(p) == EXIT_FAILURE)
	// 	exit(EXIT_FAILURE);
	//handle_assignments
	if (handle_redirection(p->redi, p) == EXIT_FAILURE)
		exit(EXIT_FAILURE);
	set_process_group_id(j, getpid());
	if (j->foreground)
		ft_tcsetpgrp(STDIN_FILENO, j->pgid);
	sig_controller(CHILD);
	// set_stdin_stdout_stderr_channels(p->stdin, p->stdout, p->stderr);
	exit(lauch_process(j, p));
}

int is_execute_on_parent_process(int foreground, char *cmd_name)
{
	if (!foreground)
		return (0);
	if (ft_strequ(cmd_name, "exit") || \
		ft_strequ(cmd_name, "cd") || \
		ft_strequ(cmd_name, "setenv") || \
		ft_strequ(cmd_name, "unsetenv") || \
		ft_strequ(cmd_name, "fg") || \
		ft_strequ(cmd_name, "bg"))
		return (1);
	return (0);
}

int lauch_process_which_can_change_shell(t_job *j, t_process *p)
{
	if(ft_strequ(p->av[0], "exit"))
		return (ft_exit(EXIT_SUCCESS));
	else if (ft_strequ(p->av[0], "cd"))
		return (ft_cd(p));
	else if (ft_strequ(p->av[0], "setenv"))
		return (ft_setenv(p));
	else if (ft_strequ(p->av[0], "unsetenv"))
		return (ft_unsetenv(p));
	else if (ft_strequ(p->av[0], "fg"))
		return (ft_fg(j, p));
	else if (ft_strequ(p->av[0], "bg"))
		return (ft_bg(j, p));
	return (EXIT_FAILURE);
}

int lauch_in_parent_process(t_job *j, t_process *p)
{
	int saved_stdin;
	int saved_stdout;
	int saved_stderr;
	int ret;

	if (handle_redirection(p->redi, p) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (p->stdin != 0)
		saved_stdin = dup(0);
	if (p->stdout != 1)
		saved_stdout = dup(1);
	if (p->stderr != 2)
		saved_stderr = dup(2);
	set_stdin_stdout_stderr_channels(p->stdin, p->stdout, p->stderr);
	ret = lauch_process_which_can_change_shell(j, p);
	if (p->stdin != 0)
		dup2(saved_stdin, STDIN_FILENO);
	if (p->stdout != 1)
		dup2(saved_stdout, STDOUT_FILENO);
	if (p->stderr != 2)
		dup2(saved_stderr, STDERR_FILENO);
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
		perror("fork"); // manage error here
		exit(EXIT_FAILURE);
	}
	p->pid = pid;
	set_process_group_id(j, pid);
}

void	lauch_simple_command(t_job *j, t_process *p)
{	
	if (is_execute_on_parent_process(j->foreground, p->av[0]))
	{
		p->status = lauch_in_parent_process(j, p);
		p->completed = COMPLETED;
	}
	else
		fork_and_lauch_in_child_process(j, p);
}
