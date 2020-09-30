/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthan <dthan@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/08 08:06:41 by dthan             #+#    #+#             */
/*   Updated: 2020/09/30 06:42:57 by dthan            ###   ########.fr       */
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

static void		builtins_printing(t_process *p)
{
	int status;

	status = 0;
	if (!ft_strcmp(p->av[0], "type"))
		ft_type(p);
	else if (!ft_strcmp(p->av[0], "echo"))
		status = ft_echo(p);
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

static int		builtins_not_printing(t_process *coms)
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

// int				run(t_exe *c)
// {
// 	char		*path;
// 	int			status;
// 	pid_t		cpid;

// 	path = NULL;
// 	status = 0;
// 	if (is_builtin_not_printing(c->av[0]))
// 		return (builtins_not_printing(c));
// 	if ((cpid = fork()) == 0)
// 	{
// 		if (c->redi != NULL)
// 			handle_redirect(*c);
// 		setpgid(0, 0);
// 		ft_tcsetpgrp(STDIN_FILENO, getpgrp());
// 		sig_controller(CHILD);
// 		if (is_builtin_printing(c->av[0]))
// 			builtins_printing(c);
// 		else if ((path = is_in_path(c)))
// 			return (make_child_path(c, path));
// 		else if (possible_to_access_file(c))
// 			make_child_binary(c);
// 		else if (c->av[0][0] != '.' && c->av[0][0] != '/')
// 			error_monitor(c->av[0], ": command not found", NULL, EXIT_FAILURE);
// 		ft_exit(EXIT_FAILURE);
// 	}
// 	else
// 		wait(NULL);
// 	// {
		
// 	// 	setpgid(cpid, cpid);
// 	// 	ft_tcsetpgrp(STDIN_FILENO, cpid);
// 	// 	waitpid(cpid, &status, WUNTRACED);
// 	// 	//WIFSTOPPED(status);
// 	// 	ft_tcsetpgrp(STDIN_FILENO, getpid());
// 	// 	tcsetattr(STDIN_FILENO, TCSADRAIN, &g_shell.shell_tmode);
// 	// }
// 	return (status);
// }

void lauch_child_process(t_job *j, t_process *p)
{
	pid_t pid;
	char	*path;

	path = NULL;
	if (p->redi != NULL)
		handle_redirect(p->redi, p);
	pid = getpid();
	// ft_printf("From child: %d\n", pid);
	if (j->pgid == 0)
		j->pgid = pid;
	setpgid(pid, j->pgid);
	if (j->foreground)
		ft_tcsetpgrp(STDIN_FILENO, j->pgid);
	sig_controller(CHILD);
	/* Set the standard input/output channels of the new process*/
	if (p->stdin != STDIN_FILENO)
	{
		dup2(p->stdin, STDIN_FILENO);
		close(p->stdin);
	}
	if (p->stdout != STDOUT_FILENO)
	{
		dup2(p->stdout, STDOUT_FILENO);
		close(p->stdout);
	}
	if (p->stderr != STDERR_FILENO)
	{
		dup2(p->stderr, STDERR_FILENO);
		close(p->stderr);
	}
	/* NOTE: Very not sure about this part */
	if (is_builtin_printing(p->av[0]))
		builtins_printing(p);
	else if ((path = is_in_path(p)))
		make_child_path(p, path); //return sth here
	else if (possible_to_access_file(p))
		make_child_binary(p);
	else if (p->av[0][0] != '.' && p->av[0][0] != '/')
		error_monitor(p->av[0], ": command not found", NULL, EXIT_FAILURE);
	ft_exit(EXIT_FAILURE);
}

int				lauch_process(t_job *j, t_process *p)
{
	int			status;
	pid_t		cpid;
	
	// if backjground
	// add process in the list of job or maybe not
	status = 0;
	// will take care the printing builtin no priting later
	if (is_builtin_not_printing(p->av[0]))
		return (builtins_not_printing(p));
	if ((cpid = fork()) == 0)
		lauch_child_process(j, p);
	else if (cpid < 0)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	else
	{
		// ft_printf("From parent: %d\n", cpid);
		if (j->pgid == 0)
			j->pgid = cpid;
		setpgid(cpid, j->pgid);
	}
	// {
		
	// 	setpgid(cpid, cpid);
	// 	ft_tcsetpgrp(STDIN_FILENO, cpid);
	// 	waitpid(cpid, &status, WUNTRACED);
	// 	//WIFSTOPPED(status);
	// 	ft_tcsetpgrp(STDIN_FILENO, getpid());
	// 	tcsetattr(STDIN_FILENO, TCSADRAIN, &g_shell.shell_tmode);
	// }
	return (status);
}

// int				run(t_exe *c, t_job *job)
// {
// 	char		*path;
// 	int			status;
// 	pid_t		cpid;

// 	path = NULL;
// 	status = 0;
// 	if (is_builtin_not_printing(c->av[0]))
// 		return (builtins_not_printing(c));
// 	if ((cpid = fork()) == 0)
// 	{
// 		if (c->redi != NULL)
// 			handle_redirect(*c);
// 		setpgid(0, 0);
// 		ft_tcsetpgrp(STDIN_FILENO, getpgrp());
// 		sig_controller(CHILD);
// 		if (is_builtin_printing(c->av[0]))
// 			builtins_printing(c);
// 		else if ((path = is_in_path(c)))
// 			return (make_child_path(c, path));
// 		else if (possible_to_access_file(c))
// 			make_child_binary(c);
// 		else if (c->av[0][0] != '.' && c->av[0][0] != '/')
// 			error_monitor(c->av[0], ": command not found", NULL, EXIT_FAILURE);
// 		ft_exit(EXIT_FAILURE);
// 	}
// 	else
// 		wait(NULL);
// 	// {
		
// 	// 	setpgid(cpid, cpid);
// 	// 	ft_tcsetpgrp(STDIN_FILENO, cpid);
// 	// 	waitpid(cpid, &status, WUNTRACED);
// 	// 	//WIFSTOPPED(status);
// 	// 	ft_tcsetpgrp(STDIN_FILENO, getpid());
// 	// 	tcsetattr(STDIN_FILENO, TCSADRAIN, &g_shell.shell_tmode);
// 	// }
// 	return (status);
// }

// void			executor(t_astnode *ast)
// {
// 	t_exe exec;

// 	printBinaryTree(ast);
// 	ft_bzero(&exec, sizeof(t_exe));
// 	exec.av = (char**)malloc(sysconf(_SC_ARG_MAX));
// 	find_heredoc(ast, &exec);
// 	execute_complete_command(ast, &exec);
// 	clear_ast(ast);
	// clear_exe(&exec);
// }

// we can use lstdel here
void	clear_heredoc(t_list *heredoc)
{
	t_list *temp;

	while(heredoc)
	{
		temp = heredoc;
		heredoc = heredoc->next;
		free(temp->content);
		free(temp);
	}
}

void			executor(t_astnode *ast)
{
	// t_exe exec;
	t_list *heredoc;

	heredoc = NULL;
	printBinaryTree(ast);
	// ft_bzero(&exec, sizeof(t_exe));
	// exec.av = (char**)malloc(sysconf(_SC_ARG_MAX));
	find_heredoc(ast, heredoc);
	execute_complete_command(ast, heredoc);
	clear_heredoc(heredoc);
	clear_ast(ast);
}

