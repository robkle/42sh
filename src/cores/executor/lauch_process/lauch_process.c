/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lauch_process.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihwang <ihwang@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/05 03:14:55 by dthan             #+#    #+#             */
/*   Updated: 2021/02/03 16:41:08 by ihwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int		is_execute_on_parent_process(int foreground, char *cmd_name)
{
	if (!foreground)
		return (0);
	if (ft_strequ(cmd_name, "exit") ||
		ft_strequ(cmd_name, "alias") ||
		ft_strequ(cmd_name, "unalias") ||
		ft_strequ(cmd_name, "cd") ||
		ft_strequ(cmd_name, "setenv") ||
		ft_strequ(cmd_name, "unsetenv") ||
		ft_strequ(cmd_name, "jobs") ||
		ft_strequ(cmd_name, "fg") ||
		ft_strequ(cmd_name, "bg") ||
		ft_strequ(cmd_name, "fc") ||
		ft_strequ(cmd_name, "export") ||
		ft_strequ(cmd_name, "set") ||
		ft_strequ(cmd_name, "unset") ||
		ft_strequ(cmd_name, "echo") ||
		ft_strequ(cmd_name, "hash") ||
		ft_strequ(cmd_name, "type"))
		return (1);
	return (0);
}

char	*is_in_hashtable(char *name)
{
	int		index;
	t_hash	*tmp;

	index = hash_index(name);
	tmp = g_shell.hashtable[index];
	while (tmp != NULL)
	{
		if (ft_strcmp(tmp->name, name) == 0)
		{
			tmp->hits++;
			return (tmp->path);
		}
		tmp = tmp->next;
	}
	return (NULL);
}

char	*get_path(t_process *p)
{
	char *path;

	path = NULL;
	if (ft_strchr(p->av[0], '/'))
		return (NULL);
	if ((path = is_in_hashtable(p->av[0])))
		return (path);
	else
	{
		if ((path = find_executable(p->av[0])) != NULL)
			add_hashentry(p->av[0], path, 1);
		return (path);
	}
}

int		lauch_simple_command(t_job *j, t_process *p)
{
	char *path;

	path = NULL;
	if (handle_expansion(p) == EXIT_FAILURE)
	{
		p->status = EXIT_FAILURE;
		p->completed = COMPLETED;
		return (EXIT_FAILURE);
	}
	if (is_execute_on_parent_process(j->foreground, p->av[0]))
	{
		p->status = lauch_in_parent_process(p);
		p->completed = COMPLETED;
		return (p->status);
	}
	path = get_path(p);
	fork_and_launch_in_child_process(j, p, path);
	return (g_shell.exit_status);
}
