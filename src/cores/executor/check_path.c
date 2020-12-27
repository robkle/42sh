/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_path.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthan <dthan@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/03 18:52:07 by ihwang            #+#    #+#             */
/*   Updated: 2020/12/27 18:10:57 by dthan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static int	is_in_path_sub(char *str, t_process *c)
{
	DIR		*dirp;
	t_dirent	*dir;

	if ((dirp = opendir(str)))
	{
		while ((dir = readdir(dirp)))
		{
			if (!ft_strcmp(dir->d_name, c->av[0]))
			{
				closedir(dirp);
				return (1);
			}
		}
		closedir(dirp);
	}
	return (0);
}

static char	**check_path(t_process *c)
{
	char	*path;

	if (c->av[0][0] == '.' || c->av[0][0] == '/')
		return (NULL);
	if ((path = ft_getenv("PATH")))
		return (ft_strsplit(path, ':'));
	else
		return (NULL);
}

int		is_in_path(t_process *c)
{
	int		i;
	int		nb;
	char	**split;

	if (!(split = check_path(c)))
		return (0);
	nb = -1;
	while (split[++nb])
		NULL;
	i = -1;
	while (++i < nb)
	{
		if (is_in_path_sub(split[i], c))
		{
			ft_strlst_del(&split, nb + 1);
			return (1);
		}
	}
	ft_strlst_del(&split, nb + 1);
	return (0);
}

char		*build_path(t_process *c)
{
	int		i;
	int		nb;
	char	**split;
	char	*path;

	if (!(split = check_path(c)))
		return (NULL);
	nb = -1;
	while (split[++nb])
		NULL;
	i = -1;
	while (++i < nb)
	{
		if (is_in_path_sub(split[i], c))
		{
			path = ft_strnew(PATH_MAX);
			ft_strcpy(path, split[i]);
			ft_strlst_del(&split, nb + 1);
			return (path);
		}
	}
	ft_strlst_del(&split, nb + 1);
	return (NULL);
}
