/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   children.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthan <dthan@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/04 14:14:05 by ihwang            #+#    #+#             */
/*   Updated: 2021/03/12 21:54:36 by dthan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int		make_child_binary(t_process *p)
{
	t_stat	sb;
	char	buf[PATH_MAX];

	lstat(p->av[0], &sb);
	if ((sb.st_mode & F_TYPE_MASK) != S_IFREG)
	{
		ft_dprintf(2, "%s: %s: is a directory\n", SHELL_NAME, p->av[0]);
		return (EXIT_FAILURE);
	}
	ft_strcpy(buf, p->av[0]);
	execve(buf, p->av, g_shell.env);
	return (EXIT_FAILURE);
}

int		make_child_path_sub(t_process *c, char *path)
{
	execve(path, c->av, g_shell.env);
	free(path);
	return (EXIT_FAILURE);
}
