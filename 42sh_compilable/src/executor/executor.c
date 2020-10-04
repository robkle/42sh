/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthan <dthan@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/08 08:06:41 by dthan             #+#    #+#             */
/*   Updated: 2020/10/01 06:25:43 by dthan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static char		*builtin_status(t_exe *coms)
{
	char		*ret_builtin;

	ret_builtin = NULL;
	if (ft_strequ(coms->av[0], "exit"))
		ft_exit(EXIT_SUCCESS);
	else if (check_intern_var_syntax(coms->av[0], NULL))
		ret_builtin = ft_set_intern_var(coms);
	else if (ft_strequ(coms->av[0], "export"))
		ret_builtin = ft_export(coms);
	else if (ft_strequ(coms->av[0], "unset"))
		ret_builtin = ft_unset(coms, &g_env);
	else if (ft_strequ(coms->av[0], "cd"))
		ret_builtin = ft_cd(coms);
	return (ret_builtin);
}

static void		builtin_printings(t_exe *coms)
{
	if (ft_strequ(coms->av[0], "pwd"))
		ft_exit(ft_pwd());
	else if (ft_strequ(coms->av[0], "env"))
		ft_exit(ft_env());
	else if (ft_strequ(coms->av[0], "echo"))
		ft_exit(ft_echo(coms));
	else if (ft_strequ(coms->av[0], "set"))
		ft_exit(ft_set());
}

static void		print_ret_builtin(char *ret_builtin)
{
	if (ret_builtin == NULL)
		return ;
	else if (ft_strequ(ret_builtin, "success"))
		ft_exit(EXIT_SUCCESS);
	else if (ft_strequ(ret_builtin, "ft_env"))
	{
		ft_env();
		ft_exit(EXIT_SUCCESS);
	}
	else
	{
		ft_putstr_fd(ret_builtin, STDERR_FILENO);
		ft_exit(EXIT_FAILURE);
	}
}

int				run(t_exe *c)
{
	char		*path;
	char		*ret_builtin;
	int			status;

	path = NULL;
	status = 0;
	ret_builtin = builtin_status(c);
	if (fork() == 0)
	{
		if (c->redi != NULL)
			handle_redirect(*c);
		print_ret_builtin(ret_builtin);
		builtin_printings(c);
		if ((path = is_in_path(c)))
			return (make_child_path(c, path));
		else if (possible_to_access_file(c))
			make_child_binary(c);
		else if (c->av[0][0] != '.' && c->av[0][0] != '/')
			error_monitor(c->av[0], ": command not found", NULL, EXIT_FAILURE);
		ft_exit(EXIT_FAILURE);
	}
	else
		wait(&status);
	ret_builtin ? ft_strdel(&ret_builtin) : NULL;
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
