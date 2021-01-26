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

unsigned int	hash_index(char *name)
{
	unsigned int	index;
	int				i;

	index = 0;
	i = 0;
	while (name[i] != '\0')
	{
		index = index + name[i];
		index = index % MAX_HASH;
		i++;
	}
	return (index);
}

t_hash			*create_hash_node(char *name, char *path, int hits)
{
	t_hash *new;

	new = NULL;
	if ((new = (t_hash*)malloc(sizeof(t_hash))))
	{
		new->name = ft_strdup(name);
		new->path = ft_strdup(path);
		new->hits = hits;
		new->next = NULL;
		new->prev = NULL;
	}
	return (new);
}

void			destroy_arr(char **arr)
{
	int i;

	i = 0;
	while (arr[i] != NULL)
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

char			*search_path(char *name, char *path)
{
	DIR				*dir;
	struct dirent	*dirent;
	char			*file_path;
	char			*tmp;

	if ((dir = opendir(path)))
	{
		while ((dirent = readdir(dir)) != NULL)
		{
			if (ft_strcmp(dirent->d_name, name) == 0)
			{
				if ((tmp = ft_strjoin(path, "/")))
				{
					if ((file_path = ft_strjoin(tmp, name)))
					{
						free(tmp);
						closedir(dir);
						return (file_path);
					}
				}
			}
		}
		closedir(dir);
	}
	return (NULL);
}

char			*find_executable(char *name)
{
	char	*path;
	char	**paths;
	char	*file_path;
	int		i;

	i = 0;
	if ((path = ft_getenv("PATH")))
	{
		if ((paths = ft_strsplit(path, ':')))
		{
			while (paths[i] != NULL)
			{
				if ((file_path = search_path(name, paths[i])) != NULL)
				{
					destroy_arr(paths);
					return (file_path);
				}
				i++;
			}
		}
		destroy_arr(paths);
	}
	return (NULL);
}
