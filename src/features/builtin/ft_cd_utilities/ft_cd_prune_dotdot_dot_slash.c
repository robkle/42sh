/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd_prune_dotdot_dot_slash.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihwang <ihwang@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/02 17:39:47 by ihwang            #+#    #+#             */
/*   Updated: 2021/03/23 14:45:43 by ihwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static char		check_access(t_cd *cd)
{
	t_stat		sb;

	stat(cd->curpath, &sb);
	if (access(cd->curpath, F_OK))
	{
		ft_dprintf(STDERR_FILENO, "%s: cd: %s: No such file or directory\n", \
		SHELL_NAME, cd->directory);
		return (EXIT_FAILURE);
	}
	else if ((sb.st_mode & F_TYPE_MASK) != S_IFDIR)
	{
		ft_dprintf(STDERR_FILENO, "%s: cd: %s: Not a directory\n", \
		SHELL_NAME, cd->directory);
		return (EXIT_FAILURE);
	}
	else if (access(cd->curpath, X_OK))
	{
		ft_dprintf(STDERR_FILENO, "%s: cd: %s: Permission denied\n", \
		SHELL_NAME, cd->directory);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

static void		update_new_curpath(char **new_curpath, char *path)
{
	char		*target;

	if ((*new_curpath)[ft_strlen(*new_curpath) - 1] != '/')
		*new_curpath = ft_strjoin_and_free_string1(*new_curpath, "/");
	target = ft_strjoin(*new_curpath, path);
	if (is_root_dir(*new_curpath) && is_root_dir(target))
		ft_strdel(&target);
	else
	{
		ft_strdel(new_curpath);
		*new_curpath = target;
	}
}

static void		prune(char **paths, char **new_curpath)
{
	int			i;
	char		*slash;

	*new_curpath = ft_strdup("/");
	i = -1;
	while (paths[++i] != NULL)
	{
		if (ft_strequ(paths[i], "..") && i != 0 && !is_root_dir(*new_curpath) \
		&& !ft_strequ(&(*new_curpath)[ft_strlen(*new_curpath) - 2], ".."))
		{
			slash = ft_strrchr(*new_curpath, '/');
			if (slash != *new_curpath)
				*slash = '\0';
			else
				*(++slash) = '\0';
			continue;
		}
		if (ft_strequ(paths[i], "."))
			continue;
		update_new_curpath(new_curpath, paths[i]);
	}
}

static char		**split_paths(char *curpath, int *path_len)
{
	char		**paths;
	char		**temp;
	int			i;

	temp = ft_strsplit(curpath, '/');
	*path_len = 0;
	while (temp[*path_len])
		(*path_len)++;
	if (curpath[0] == '/')
	{
		paths = (char**)ft_memalloc(sizeof(char*) * (*path_len + 2));
		paths[0] = ft_strdup("/");
		i = 0;
		while (++i < *path_len + 1)
			paths[i] = ft_strdup(temp[i - 1]);
		ft_strlst_del(&temp, *path_len);
		(*path_len)++;
	}
	else
		paths = temp;
	return (paths);
}

/*
**	step8 in posix doc
*/

int				ft_cd_prune_dotdot_dot_slash(t_cd *cd)
{
	int			path_len;
	char		**paths;
	char		*new_curpath;

	paths = split_paths(cd->curpath, &path_len);
	if (paths[0] == NULL)
	{
		free(paths);
		return (ft_cd_compress_curpath(cd));
	}
	prune(paths, &new_curpath);
	ft_strlst_del(&paths, path_len);
	ft_strdel(&cd->curpath);
	cd->curpath = new_curpath;
	if ((check_access(cd)) == EXIT_FAILURE)
	{
		ft_strdel(&cd->curpath);
		return (EXIT_FAILURE);
	}
	return (ft_cd_compress_curpath(cd));
}
