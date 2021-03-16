/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash_table_tools.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthan <dthan@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/12 20:17:25 by dthan             #+#    #+#             */
/*   Updated: 2021/03/12 20:22:27 by dthan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

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

	if (p->av[0] == NULL)
		return (NULL);
	path = NULL;
	if (ft_strchr(p->av[0], '/'))
		return (NULL);
	if ((path = is_in_hashtable(p->av[0])))
		return (path);
	else
	{
		if ((path = find_executable(p->av[0])) != NULL)
		{
			add_hashentry(p->av[0], path, 0);
			free(path);
			path = is_in_hashtable(p->av[0]);
		}
		return (path);
	}
}
