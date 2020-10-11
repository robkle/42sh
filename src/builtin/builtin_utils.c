/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihwang <ihwang@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/05 03:20:48 by dthan             #+#    #+#             */
/*   Updated: 2020/10/11 06:17:53 by ihwang           ###   ########.fr       */
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
		ft_strequ(comm, "pwd") || \
		ft_strequ(comm, "fg"))
		return (1);
	return (0);
}

int		builtins_not_printing(t_process *p)
{
	p->completed = COMPLETED;
	if (!ft_strcmp(p->av[0], "exit"))
		ft_exit(EXIT_SUCCESS);
	if (!ft_strcmp(p->av[0], "pwd"))
		return (p->status = ft_pwd());
	else if (!ft_strcmp(p->av[0], "cd"))
		return (p->status = ft_cd(p));
	else if (!ft_strcmp(p->av[0], "env"))
		return (p->status = ft_env());
	else if (!ft_strcmp(p->av[0], "setenv"))
		return (p->status = ft_setenv(p));
	else if (!ft_strcmp(p->av[0], "unset"))
		NULL;
		//return (p->status = ft_unset(p, &g_shell.env));
	else if (ft_strequ(p->av[0], "fg"))
		return (p->status = ft_fg());
	return (EXIT_FAILURE);
}
