/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_in_child_process.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthan <dthan@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/12 20:45:47 by dthan             #+#    #+#             */
/*   Updated: 2021/03/19 19:19:03 by dthan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static int	is_builtin(char *cmd_name)
{
	if (ft_strequ(cmd_name, "exit") ||
		ft_strequ(cmd_name, "cd") ||
		ft_strequ(cmd_name, "env") ||
		ft_strequ(cmd_name, "jobs") ||
		ft_strequ(cmd_name, "fg") ||
		ft_strequ(cmd_name, "bg") ||
		ft_strequ(cmd_name, "echo") ||
		ft_strequ(cmd_name, "set") ||
		ft_strequ(cmd_name, "unset") ||
		ft_strequ(cmd_name, "hash") ||
		ft_strequ(cmd_name, "type") ||
		ft_strequ(cmd_name, "export") ||
		ft_strequ(cmd_name, "alias") ||
		ft_strequ(cmd_name, "unalias") ||
		ft_strequ(cmd_name, "fc"))
		return (1);
	return (0);
}

static int	exec_builtin2(t_job *j, t_process *p)
{
	if (ft_strequ(p->av[0], "echo"))
		return (ft_echo(p));
	else if (ft_strequ(p->av[0], "type"))
		return (ft_type(p));
	else if (ft_strequ(p->av[0], "set"))
		return (ft_set());
	else if (ft_strequ(p->av[0], "unset"))
		return (ft_unset(p->ac, p->av));
	else if (ft_strequ(p->av[0], "hash"))
		return (ft_hash(p));
	else if (ft_strequ(p->av[0], "export"))
		return (ft_export(p->ac, p->av));
	else if (ft_strequ(p->av[0], "alias"))
		return (ft_alias(p));
	else if (ft_strequ(p->av[0], "unalias"))
		return (ft_unalias(p));
	else if (ft_strequ(p->av[0], "fc"))
		return (ft_fc(p, j->foreground));
	return (EXIT_FAILURE);
}

static int	exec_builtin(t_job *j, t_process *p)
{
	if (ft_strequ(p->av[0], "exit"))
		ft_exit(p);
	else if (ft_strequ(p->av[0], "cd"))
		return (ft_cd(p));
	else if (ft_strequ(p->av[0], "env"))
		return (ft_env());
	else if (ft_strequ(p->av[0], "jobs"))
		return (ft_jobs(p));
	else if (ft_strequ(p->av[0], "fg"))
		return (ft_fg_child());
	else if (ft_strequ(p->av[0], "bg"))
		return (ft_bg_child());
	return (exec_builtin2(j, p));
}

static int	possible_to_access_file(t_process *p)
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
			ft_dprintf(2, "%s: Permission denied: %s\n", \
				SHELL_NAME, p->av[0]);
			return (0);
		}
		else
			return (1);
	}
	else
		return (0);
}

int			execute_in_child_process(t_job *j, t_process *p, char *path)
{
	if (p->av[0] == NULL)
		return (EXIT_SUCCESS);
	if (ft_strchr(p->av[0], '/') != NULL && possible_to_access_file(p))
		return (make_child_binary(p));
	else if (is_builtin(p->av[0]))
		return (exec_builtin(j, p));
	else if (path != NULL)
		return (make_child_path_sub(p, path));
	else if (p->av[0][0] != '.' && p->av[0][0] != '/')
		ft_dprintf(2, "%s: %s: command not found\n", SHELL_NAME, p->av[0]);
	return (127);
}
