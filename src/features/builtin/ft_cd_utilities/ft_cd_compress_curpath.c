/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd_compress_curpath.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihwang <ihwang@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/02 17:43:17 by ihwang            #+#    #+#             */
/*   Updated: 2021/03/21 11:25:32 by ihwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

/*
**	step9 in posix doc
*/

static char	is_initial_path_of(char *curpath, char *path_var)
{
	return (ft_strnstr(curpath, path_var, ft_strlen(path_var)) != NULL);
}

static char	*cnvt_curpath_to_relative_path(char *curpath)
{
	char	*relative_path;
	char	buf[PATH_MAX];

	ft_memset(buf, 0, PATH_MAX);
	getcwd(buf, PATH_MAX);
	relative_path = &curpath[ft_strlen(buf) - 1];
	relative_path[0] = '.';
	return (ft_strdup(relative_path));
}

int			ft_cd_compress_curpath(t_cd *cd)
{
	char	*var;
	size_t	cpath_len;
	size_t	dir_len;

	cpath_len = ft_strlen(cd->curpath);
	dir_len = ft_strlen(cd->directory);
	if (cpath_len + FT_CD_NULL_LEN > PATH_MAX \
	&& dir_len + FT_CD_NULL_LEN < PATH_MAX)
	{
		var = ft_getenv("PWD");
		if (var != NULL)
			var = ft_strdup(var);
		if (var[ft_strlen(var) - 1] != '/')
			var = ft_strjoin_and_free_string1(var, "/");
		if (is_initial_path_of(cd->curpath, var))
		{
			cd->prev_curpath = cd->curpath;
			cd->curpath = cnvt_curpath_to_relative_path(cd->curpath);
		}
		free(var);
	}
	return (ft_cd_change_dir(cd));
}
