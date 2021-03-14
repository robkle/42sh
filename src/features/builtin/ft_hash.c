/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hash.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthan <dthan@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/15 23:35:55 by vgrankul          #+#    #+#             */
/*   Updated: 2021/02/16 21:07:52 by dthan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int		remove_hashentries(void)
{
	int		i;
	t_hash	*tmp;

	i = 0;
	while (i < MAX_HASH)
	{
		if (g_shell.hashtable[i])
		{
			while (g_shell.hashtable[i] != NULL)
			{
				tmp = g_shell.hashtable[i];
				g_shell.hashtable[i] = g_shell.hashtable[i]->next;
				free(tmp->name);
				free(tmp->path);
				free(tmp);
			}
			g_shell.hashtable[i] = NULL;
		}
		i++;
	}
	return (EXIT_SUCCESS);
}

int		print_hashtable(void)
{
	int		i;
	int		found;
	t_hash	*tmp;

	i = 0;
	found = 0;
	while (i < MAX_HASH)
	{
		if (g_shell.hashtable[i])
		{
			if (found == 0)
				ft_printf("hits     command\n");
			tmp = g_shell.hashtable[i];
			found++;
			while (tmp != NULL)
			{
				ft_printf("%4d     %s\n", tmp->hits, tmp->path);
				tmp = tmp->next;
			}
		}
		i++;
	}
	if (found == 0)
		ft_printf("hash: hash table empty\n");
	return (EXIT_SUCCESS);
}

void	add_hashentry(char *name, char *path, int hits)
{
	int		index;
	t_hash	*new;
	t_hash	*tmp;

	index = hash_index(name);
	if (exists_in_hashtable(name, path, index) == 1)
	{
		if ((new = create_hash_node(name, path, hits)))
		{
			tmp = g_shell.hashtable[index];
			if (g_shell.hashtable[index] == NULL)
			{
				new->prev = NULL;
				g_shell.hashtable[index] = new;
			}
			else
			{
				while (tmp->next != NULL)
					tmp = tmp->next;
				tmp->next = new;
				new->prev = tmp;
			}
		}
	}
}

int		hash_loop(t_process *c)
{
	int		i;
	int		status;
	char	*path;

	i = 0;
	path = NULL;
	status = 0;
	while (c->av[++i] != NULL)
	{
		if ((path = find_executable(c->av[i])))
		{
			add_hashentry(c->av[i], path, 0);
			free(path);
		}
		else
		{
			ft_printf("hash: %s: not found\n", c->av[i]);
			status = EXIT_FAILURE;
		}
	}
	return (status);
}

int		ft_hash(t_process *c)
{
	int		status;

	status = 0;
	if (c->ac == 1)
		return (print_hashtable());
	else if (c->ac == 2 && ft_strcmp(c->av[1], "-r") == 0)
		return (remove_hashentries());
	else if (c->ac != 2 && ft_strcmp(c->av[1], "-r") == 0)
	{
		ft_dprintf(2, "42sh: hash: invalid option\nhash usage: hash [-r]\n");
		return (EXIT_FAILURE);
	}
	status = hash_loop(c);
	return (status);
}
