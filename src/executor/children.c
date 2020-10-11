/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   children.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihwang <ihwang@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/04 14:14:05 by ihwang            #+#    #+#             */
/*   Updated: 2020/10/10 17:26:07 by ihwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void		make_child_binary(t_process *p)
{
	t_stat	sb;
	char	buf[PATH_MAX];

	lstat(p->av[0], &sb);
	if ((sb.st_mode & F_TYPE_MASK) != S_IFREG)
	{
		error_monitor(p->av[0], ": is a directory", NULL, 0);
		return ;
	}
	ft_strcpy(buf, p->av[0]);
	execve(buf, p->av, g_shell.env);
	ft_exit(EXIT_FAILURE);
}

static void	make_child_path_sub(t_process *c, char buf[])
{
	sig_controller(CHILD);
	execve(buf, c->av, g_shell.env);
	ft_exit(EXIT_FAILURE);
}

int			make_child_path(t_process *c, char *path)
{
	char	buf[PATH_MAX];

	ft_strcpy(buf, path);
	ft_strdel(&path);
	if (access(buf, X_OK))
	{
		ft_putstr_fd(buf, 2);
		ft_putstr_fd(": Permission denied\n", 2);
		return (0);
	}
	ft_strcat(buf, "/");
	ft_strcat(buf, c->av[0]);
	if (!access(buf, X_OK))
		make_child_path_sub(c, buf);
	else
	{
		ft_putstr_fd(buf, 2);
		ft_putstr_fd(": Permission denied\n", 2);
	}
	ft_exit(EXIT_SUCCESS);
	return (0);
}
