/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hash.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgrankul <vgrankul@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/15 23:35:55 by vgrankul          #+#    #+#             */
/*   Updated: 2020/12/26 11:43:35 by vgrankul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	remove_hashentries(void)
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
}

void	print_hashtable(void)
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
}

int		exists_in_hashtable(char *name, char *path, int index)
{
	t_hash *tmp;

	tmp = g_shell.hashtable[index];
	while (tmp != NULL)
	{
		if (ft_strcmp(tmp->name, name) == 0)
		{
			free(tmp->path);
			tmp->path = ft_strdup(path);
			tmp->hits = 0;
			return (0);
		}
		tmp = tmp->next;
	}
	return (1);
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

int		ft_hash(t_process *c)
{
	int		i;
	char	*path;

	i = 0;
	if (c->ac == 1)
		print_hashtable();
	else if (c->ac == 2 && ft_strcmp(c->av[1], "-r") == 0)
		remove_hashentries();
	else if (c->ac != 2 && ft_strcmp(c->av[1], "-r") == 0)
	{
		ft_dprintf(2, "42sh: hash: invalid option\nhash usage: hash [-r]\n");
		return (-1);
	}
	else
	{
		while (c->av[++i] != NULL)
		{
			if ((path = find_executable(c->av[i])))
				add_hashentry(c->av[i], path, 0);
			else
				ft_printf("hash: %s: not found\n", c->av[i]);
			free(path);
		}
	}
	return (0);
}
