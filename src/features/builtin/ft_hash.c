/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hash.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthan <vgrankul@student.hive.fi>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/15 23:35:55 by vgrankul          #+#    #+#             */
/*   Updated: 2020/12/26 11:43:35 by vgrankul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	destroy_arr(char **arr)
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

void    remove_hashentries()
{
    int i;
    t_hash *tmp;

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

void    print_hashtable()
{
    int i;
	int found;
    t_hash *tmp;

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

unsigned int     hash_index(char *name)
{
    unsigned int index;
    int i;

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

t_hash    *create_hash_node(char *name, char *path, int hits)
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

int		exists_in_hashtable(char *name, char *path, int index)
{
	t_hash *tmp;

	tmp = g_shell.hashtable[index];
	while(tmp != NULL)
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

void    add_hashentry(char *name, char *path)
{
    int index;
    t_hash *new;
    t_hash *tmp;

    index = hash_index(name);
	if (exists_in_hashtable(name, path, index) == 1)
	{
    	if ((new = create_hash_node(name, path, 0)))
    	{
        	tmp = g_shell.hashtable[index];
        	if (g_shell.hashtable[index] == NULL)
        	{
            	new->prev = NULL;
				g_shell.hashtable[index] = new;
			}
			else
			{
				while (tmp != NULL)
					tmp = tmp->next;
				tmp->next = new;
				new->prev = tmp;
			}
    	}
	}
}

char	*search_path(char *name, char *path)
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

char	*find_executable(char *name)
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
    //bash: hash: fs: not found
	return (NULL);
}

int ft_hash(t_process *c)
{
    int i;
    char *path;

    i = 1;
    if (c->ac == 1)
	{
		print_hashtable();
		return (0);
	}
    if(c->ac == 2 && ft_strcmp(c->av[1], "-r") == 0)
        remove_hashentries();
    else if (c->ac != 2 && ft_strcmp(c->av[1], "-r") == 0)
    {
        ft_dprintf(2, "42sh: hash: invalid option\n hash usage: hash [-r]\n");
        return (-1);
    }
    else
    {
        while (c->av[i] != NULL)
        {
            if ((path = find_executable(c->av[i])))
            {
                add_hashentry(c->av[i], path);
                free(path);
            }
			else
				ft_printf("hash: %s: not found\n", c->av[i]);
			
            i++;
        }
    }
    return (0);
}