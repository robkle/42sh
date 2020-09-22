/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihwang <ihwang@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/08 08:06:41 by dthan             #+#    #+#             */
/*   Updated: 2020/09/23 00:40:59 by ihwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static int		is_builtin_printing(char *comm)
{
	if (!ft_strcmp(comm, "type") || !ft_strcmp(comm, "hash") || \
			!ft_strcmp(comm, "echo"))
		return (1);
	return (0);
}

static void		builtins_printing(t_exe *coms)
{
	int status;

	status = 0;
	if (!ft_strcmp(coms->av[0], "type"))
		ft_type(coms);
	else if (!ft_strcmp(coms->av[0], "echo"))
		status = ft_echo(coms);
/*	else if (ft_strequ(coms->av[0], "fg"))
		status = ft_fg(coms);
	else if (ft_strequ(coms->av[0], "bg"))
		status = ft_bg(coms);
	else if (ft_strequ(coms->av[0], "jobs"))
		status = ft_jobs(coms);*/
	//else if (!ft_strcmp(coms->av[0], "hash"))
		//ft_hash(coms);
	ft_exit(status);
}

static int		is_builtin_not_printing(char *comm)
{
	if (!ft_strcmp(comm, "exit") || !ft_strcmp(comm, "cd") || \
			!ft_strcmp(comm, "env") || !ft_strcmp(comm, "setenv") || \
			!ft_strcmp(comm, "unsetenv") || !ft_strcmp(comm, "pwd"))
		return (1);
	return (0);
}

static int		builtins_not_printing(t_exe *coms)
{
	if (!ft_strcmp(coms->av[0], "exit"))
		ft_exit(EXIT_SUCCESS);
	if (!ft_strcmp(coms->av[0], "pwd"))
		return (ft_pwd());
	else if (!ft_strcmp(coms->av[0], "cd"))
		return (ft_cd(coms));
	else if (!ft_strcmp(coms->av[0], "env"))
		return (ft_env());
	else if (!ft_strcmp(coms->av[0], "setenv"))
		return (ft_setenv(coms));
	else if (!ft_strcmp(coms->av[0], "unsetenv"))
		return (ft_unsetenv(coms));
	return (EXIT_FAILURE);
}

// g_shell.job = ft_memalloc(sizeof(t_list));
// g_shell.job->content = ft_memalloc(sizeof(t_job));
// g_shell.job->content_size = sizeof(t_job);

int				run(t_exe *c)
{
	char		*path;
	int			status;
	pid_t		cpid;
	t_job		*p_job;

	path = NULL;
	status = 0;
	if (is_builtin_not_printing(c->av[0]))
		return (builtins_not_printing(c));
	if ((cpid = fork()) == 0)
	{
		if (c->redi != NULL)
			handle_redirect(*c);
		setpgid(0, 0);
		ft_tcsetpgrp(STDIN_FILENO, getpgrp());
		sig_controller(CHILD);
		if (is_builtin_printing(c->av[0]))
			builtins_printing(c);
		else if ((path = is_in_path(c)))
			return (make_child_path(c, path));
		else if (possible_to_access_file(c))
			make_child_binary(c);
		else if (c->av[0][0] != '.' && c->av[0][0] != '/')
			error_monitor(c->av[0], ": command not found", NULL, EXIT_FAILURE);
		ft_exit(EXIT_FAILURE);
	}
	else
	{
		
		setpgid(cpid, cpid);
		ft_tcsetpgrp(STDIN_FILENO, cpid);
		waitpid(cpid, &status, WUNTRACED);
		//WIFSTOPPED(status);
		ft_tcsetpgrp(STDIN_FILENO, getpid());
		tcsetattr(STDIN_FILENO, TCSADRAIN, &g_shell.shell_tmode);
	}
	return (status);
}

void			executor(t_astnode *ast)
{
	t_exe exec;

	printBinaryTree(ast);
	ft_bzero(&exec, sizeof(t_exe));
	exec.av = (char**)malloc(sysconf(_SC_ARG_MAX));
	find_heredoc(ast, &exec);
	execute_complete_command(ast, &exec);
	clear_ast(ast);
	clear_exe(&exec);
}
