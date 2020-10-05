/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthan <dthan@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/05 03:20:48 by dthan             #+#    #+#             */
/*   Updated: 2020/10/05 06:38:41 by dthan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int		is_builtin_printing(char *comm)
{
	if (ft_strequ(comm, "type") || \
		ft_strequ(comm, "hash") || \
		ft_strequ(comm, "echo") || \
		ft_strequ(comm, "jobs"))
		return (1);
	return (0);
}

void		builtins_printing(t_process *p)
{
	int status;

	status = 0;
	if (!ft_strcmp(p->av[0], "type"))
		ft_type(p);
	else if (!ft_strcmp(p->av[0], "echo"))
		status = ft_echo(p);
	// else if (ft_strequ(coms->av[0], "fg"))
	// 	status = ft_fg(coms);
	// else if (ft_strequ(coms->av[0], "bg"))
	// 	status = ft_bg(coms);
	else if (ft_strequ(p->av[0], "jobs"))
		status = ft_jobs();
	//else if (!ft_strcmp(coms->av[0], "hash"))
		//ft_hash(coms);
	ft_exit(status);
}

int		is_builtin_not_printing(char *comm)
{
	if (ft_strequ(comm, "exit") || \
		ft_strequ(comm, "cd") || \
		ft_strequ(comm, "env") || \
		ft_strequ(comm, "setenv") || \
		ft_strequ(comm, "unsetenv") || \
		ft_strequ(comm, "pwd"))
		return (1);
	return (0);
}

int		builtins_not_printing(t_process *coms)
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
	// else if (ft_strequ(coms->av[0], "jobs")) // test jobs here
	// 	return (ft_jobs());
	return (EXIT_FAILURE);
}
