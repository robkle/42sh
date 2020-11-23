/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   children.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthan <dthan@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/04 14:14:05 by ihwang            #+#    #+#             */
/*   Updated: 2020/10/10 21:58:07 by dthan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int	make_child_binary(t_process *p)
{
	t_stat	sb;
	char	buf[PATH_MAX];

	lstat(p->av[0], &sb);
	if ((sb.st_mode & F_TYPE_MASK) != S_IFREG)
	{
		error_monitor(p->av[0], ": is a directory", NULL, 0);
		return (EXIT_FAILURE);
	}
	ft_strcpy(buf, p->av[0]);
	execve(buf, p->av, g_env);
	return (EXIT_FAILURE);
}

static int	make_child_path_sub(t_process *c, char buf[])
{
	execve(buf, c->av, g_env);
	return (EXIT_FAILURE);
}

int			make_child_path(t_process *c)
{
	char	buf[PATH_MAX];
	char	*path;

	path = build_path(c);
	ft_strcpy(buf, path);
	ft_strdel(&path);
	if (access(buf, X_OK))
	{
		ft_dprintf(2, "%s %s %s\n", SHELL_NAME, buf ,EACCES);
		return (EXIT_FAILURE);
	}
	ft_strcat(buf, "/");
	ft_strcat(buf, c->av[0]);
	if (!access(buf, X_OK))
		return (make_child_path_sub(c, buf));
	ft_dprintf(2, "%s %s %s\n", SHELL_NAME, buf ,EACCES);
	return (EXIT_FAILURE);
}
