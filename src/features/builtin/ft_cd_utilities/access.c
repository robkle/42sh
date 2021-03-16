/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   access.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthan <dthan@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/15 23:35:55 by ihwang            #+#    #+#             */
/*   Updated: 2021/03/15 23:21:37 by dthan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int				possible_to_access_dir(t_process *c)
{
	t_stat		sb;

	stat(c->av[1], &sb);
	if (access(c->av[1], F_OK))
	{
		ft_dprintf(2, "%s: cd: %s: No such file or directory\n", \
			SHELL_NAME, c->av[1]);
		return (EXIT_FAILURE);
	}
	else if ((sb.st_mode & F_TYPE_MASK) != S_IFDIR)
	{
		ft_dprintf(2, "%s: cd: %s: Not a directory\n", SHELL_NAME, c->av[1]);
		return (EXIT_FAILURE);
	}
	else if (access(c->av[1], X_OK))
	{
		ft_dprintf(2, "%s: cd: %s: Permission denied\n", SHELL_NAME, c->av[1]);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

int				possible_to_access_file(t_process *p)
{
	if (p->av[0][0] == '.' || p->av[0][0] == '/')
	{
		if (access(p->av[0], F_OK))
		{
			ft_dprintf(2, "%s: no such file or directory: %s\n", \
				SHELL_NAME, p->av[0]);
			return (0);
		}
		else if (access(p->av[0], X_OK))
		{
			ft_dprintf(2, "%s: no such file or directory: %s\n", \
				SHELL_NAME, p->av[0]);
			return (0);
		}
		else
			return (1);
	}
	else
		return (0);
}
