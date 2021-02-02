/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd_search_cdpath.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihwang <ihwang@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/02 17:31:25 by ihwang            #+#    #+#             */
/*   Updated: 2021/02/02 22:39:23 by ihwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

/*
**	step5 in posix doc
*/

static char is_valid_cdpath(t_cd *cd, char *path)
{
	size_t path_len;

	path_len = ft_strlen(path);
	if (path[path_len - 1] != '/')
		path = ft_strjoin_and_free_string1(ft_strjoin(path, "/"), cd->directory);
	else
		path = ft_strjoin(path, cd->directory);
	if (!access(path, X_OK))
	{
		ft_strdel(&path);
		return (TRUE);
	}
	else
	{
		ft_strdel(&path);
		return (FALSE);
	}
}

static char *get_curpath_from_cdpath(t_cd *cd, char *path)
{
	size_t path_len;

	path_len = ft_strlen(path);
	if (path[path_len - 1] != '/')
		path = ft_strjoin_and_free_string1(ft_strjoin((const char*)path, "/"), cd->directory);
	else
		path = ft_strjoin((const char*)path, cd->directory);
	return (path);
}

static char	is_valid_relative_path(char *directory)
{
	char	*path;

	path = ft_strdup("./");
	path = ft_strjoin_and_free_string1(path, directory);
	if (!access((const char*)path, X_OK))
	{
		ft_strdel(&path);
		return (TRUE);
	}
	else
	{
		ft_strdel(&path);
		return (FALSE);
	}
}

static char	*get_curpath_from_directory(t_cd *cd)
{
	char	*path;

	path = ft_strdup("./");
	path = ft_strjoin_and_free_string1(path, cd->directory);
	return (path);
}

int ft_cd_search_cdpath(t_cd *cd)
{
	int i;
	char **path_split;

	if(ft_getvar("CDPATH") != NULL)
	{
		path_split = ft_strsplit(ft_getvar("CDPATH")->value, ':');
		i = -1;
		while (path_split[++i])
		{
			if(cd->curpath == NULL && is_valid_cdpath(cd, path_split[i]))
			{
				cd->curpath = get_curpath_from_cdpath(cd, path_split[i]);
				cd->print_info = TRUE;
			}
		}
		ft_strlst_del(&path_split, i);
	}
	if (cd->curpath == NULL && is_valid_relative_path(cd->directory))
		cd->curpath = get_curpath_from_directory(cd);
	if (cd->curpath == NULL)
		return (ft_cd_get_curpath_from_dir(cd));
	else
		return (ft_cd_append_slash_to_curpath(cd));
}