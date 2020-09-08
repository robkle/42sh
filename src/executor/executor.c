/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihwang <ihwang@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/08 08:06:41 by dthan             #+#    #+#             */
/*   Updated: 2020/09/08 13:19:14 by ihwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static int		is_builtin(char *comm)
{
	if (ft_strequ(comm, "exit") || ft_strequ(comm, "cd") || \
			ft_strequ(comm, "env") || ft_strequ(comm, "setenv") || \
			ft_strequ(comm, "unsetenv") || ft_strequ(comm, "pwd") || \
			ft_strequ(comm, "type") || ft_strequ(comm, "hash") || \
			ft_strequ(comm, "echo"))
		return (true);
	return (false);
}

static void		run_builtin(t_exe *coms)
{
//	if (check_intern_var_syntax(coms))
	//	ft_exit(ft_set_intern_var(coms));
	if (ft_strequ(coms->av[0], "pwd"))
		ft_exit(ft_pwd());
	else if (ft_strequ(coms->av[0], "cd"))
		ft_exit(ft_cd(coms));
	else if (ft_strequ(coms->av[0], "env"))
		ft_exit(ft_env());
	else if (ft_strequ(coms->av[0], "setenv"))
		ft_exit(ft_setenv(coms));
	else if (ft_strequ(coms->av[0], "unsetenv"))
		ft_exit(ft_unsetenv(coms));
	else if (ft_strequ(coms->av[0], "echo"))
		ft_exit(ft_echo(coms));
}

int				run(t_exe *c)
{
	char		*path;
	int			status;

	path = NULL;
	status = 0;
	if (ft_strequ(c->av[0], "exit"))
		ft_exit(EXIT_SUCCESS);
	if (fork() == 0)
	{
		if (c->redi != NULL)
			handle_redirect(*c);
		if (is_builtin(c->av[0]))
			run_builtin(c);
		else if ((path = is_in_path(c)))
			return (make_child_path(c, path));
		else if (possible_to_access_file(c))
			make_child_binary(c);
		else if (c->av[0][0] != '.' && c->av[0][0] != '/')
			error_monitor(c->av[0], ": command not found", NULL, EXIT_FAILURE);
		ft_exit(EXIT_FAILURE);
	}
	else
		wait(&status);
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
