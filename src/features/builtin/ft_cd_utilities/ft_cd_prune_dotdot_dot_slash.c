/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd_prune_dotdot_dot_slash.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihwang <ihwang@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/02 17:39:47 by ihwang            #+#    #+#             */
/*   Updated: 2021/02/02 17:44:35 by ihwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

/*
**	step8 in posix doc
*/

static char		check_access(char *path)
{
	t_stat		sb;

	stat(path, &sb);
	if (access(path, F_OK))
	{
		ft_dprintf(2, "%s: cd: %s: No such file or directory\n", \
			SHELL_NAME, path);
		return (EXIT_FAILURE);
	}
	else if ((sb.st_mode & F_TYPE_MASK) != S_IFDIR)
	{
		ft_dprintf(2, "%s: cd: %s: Not a directory\n", SHELL_NAME, path);
		return (EXIT_FAILURE);
	}
	else if (access(path, X_OK))
	{
		ft_dprintf(2, "%s: cd: %s: Permission denied\n", SHELL_NAME, path);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}


int ft_cd_prune_dotdot_dot_slash(t_cd *cd)
{
    char **split;
    char *new_curpath;
    char *slash;
    int i;

    split = ft_strsplit(cd->curpath, '/');
    if (split[0] == NULL)
    {
        free(split);
        return (ft_cd_compress_curpath(cd));
    }
    new_curpath = ft_strnew(0);
    i = -1;
    while (split[++i] != NULL)
    {
        if (ft_strequ(split[i], "..") && i != 0 && !is_root_dir(new_curpath) && !ft_strequ(&new_curpath[ft_strlen(new_curpath) - 2], ".."))
        {
			if ((check_access(new_curpath)) == EXIT_FAILURE)
			{
				free(cd->curpath);
				return (EXIT_FAILURE);
			}
            slash = ft_strrchr(new_curpath, '/');
            if (slash != new_curpath)
                *slash = '\0';
            else
                *(++slash) = '\0';
            continue ;
        }
        if (ft_strequ(split[i], "."))
            continue ;
        new_curpath = ft_strjoin_and_free_string1(new_curpath, "/");
        new_curpath = ft_strjoin_and_free_string1(new_curpath, split[i]);
    }
    ft_strlst_del(&split, i);
    ft_strdel(&cd->curpath);
    cd->curpath = new_curpath;
	return (ft_cd_compress_curpath(cd));
}

