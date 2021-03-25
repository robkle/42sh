/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd_compress_curpath.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihwang <ihwang@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/02 17:43:17 by ihwang            #+#    #+#             */
/*   Updated: 2021/03/23 15:14:47 by ihwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static char	is_initial_path_of(char pwd[], char *curpath)
{
	return (ft_strnstr(pwd, curpath, ft_strlen(curpath)) != NULL);
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

/*
**	step9 in posix doc
*/

int			ft_cd_compress_curpath(t_cd *cd)
{
	char	*var;
	char	pwd[PATH_MAX];
	size_t	cpath_len;
	size_t	dir_len;

	cpath_len = ft_strlen(cd->curpath);
	dir_len = ft_strlen(cd->directory);
	if (cpath_len + FT_CD_NULL_LEN > PATH_MAX \
	&& dir_len + FT_CD_NULL_LEN < PATH_MAX)
	{
		var = ft_getenv("PWD");
		if (var == NULL)
			return (ft_cd_change_dir(cd));
		ft_strcpy(pwd, var);
		if (pwd[ft_strlen(pwd) - 1] != '/')
			ft_addchar(pwd, '/');
		if (is_initial_path_of(pwd, cd->curpath))
		{
			cd->prev_curpath = cd->curpath;
			cd->curpath = cnvt_curpath_to_relative_path(cd->curpath);
		}
	}
	return (ft_cd_change_dir(cd));
}
