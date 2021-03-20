/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   children.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihwang <ihwang@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/04 14:14:05 by ihwang            #+#    #+#             */
/*   Updated: 2021/03/20 16:41:03 by ihwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int		exec_file(t_process *p)
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

int		exec_file_in_path(t_process *c, char *path)
{
	if (access(path, X_OK))
	{
		ft_dprintf(2, "%s: %s: Permission denied\n", \
			SHELL_NAME, path);
		free(path);
		return (EXIT_FAILURE);
	}
	execve(path, c->av, g_shell.env);
	free(path);
	return (EXIT_FAILURE);
}
