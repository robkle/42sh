/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd_change_dir.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihwang <ihwang@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/02 17:45:50 by ihwang            #+#    #+#             */
/*   Updated: 2021/02/02 17:46:12 by ihwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

/*
**	step10 in posix doc
*/

static void	manipulate_var(t_cd *cd)
{
	char 	*pwd;
	char	*oldpwd;
	char	absolute_path[PATH_MAX];

	if ((pwd = ft_getenv("PWD")) && (oldpwd = ft_getenv("OLDPWD")))
		ft_strcpy(oldpwd, pwd);
	if (!(cd->opt.applied & BUILTIN_CD_OPT_P))
	{
		if (pwd && cd->prev_curpath)
			ft_strcpy(pwd, cd->prev_curpath);
		else if (pwd && cd->curpath)
			ft_strcpy(pwd, cd->curpath);
	}
	else
	{
		ft_memset((void*)absolute_path, 0, sizeof(absolute_path));
		if (getcwd(absolute_path, sizeof(absolute_path)) != NULL && pwd)
			ft_strcpy(pwd, absolute_path);
	}
    if (is_root_dir(pwd))
        ft_strcpy(pwd, "/");
}

int ft_cd_change_dir(t_cd *cd)
{
	if (chdir(cd->curpath) == -1)
	{
		ft_dprintf(2, "%s: cd: No such file or directory\n", SHELL_NAME);
		free(cd->curpath);
		return (EXIT_FAILURE);
	}
	manipulate_var(cd);
	if (cd->print_info == TRUE)
		ft_printf("%s\n", cd->curpath);
    ft_strdel(&cd->curpath);
	return (EXIT_SUCCESS);
}