/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd_change_dir.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihwang <ihwang@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/02 17:45:50 by ihwang            #+#    #+#             */
/*   Updated: 2021/03/15 22:19:00 by ihwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

/*
**	step10 in posix doc
*/

static void ft_cd_set_env(char *name, char *value)
{
	char **av;

	av = (char**)malloc(sizeof(char*) * 3);
	av[0] = (char*)malloc(ft_strlen("export") + 1);
	av[1] = (char*)malloc(ft_strlen(name) + ft_strlen(value) + 2);
	av[2] = NULL;
	ft_strcpy(av[0], "export");
	ft_strcpy(av[1], name);
	ft_strcat(av[1], "=");
	ft_strcat(av[1], value);
	ft_export(2, av);
	ft_strlst_del(&av, 2);
}

static void	manipulate_var(t_cd *cd)
{
	char	absolute_path[PATH_MAX];

	if (ft_getenv("PWD") != NULL)
		ft_cd_set_env("OLDPWD", ft_getenv("PWD"));
	else
		ft_cd_set_env("OLDPWD", "");
	getcwd(absolute_path, sizeof(absolute_path));
	if (!(cd->opt.applied & BUILTIN_CD_OPT_P))
	{
		if (cd->prev_curpath)
			ft_cd_set_env("PWD", cd->prev_curpath);
		else if (cd->curpath)
			ft_cd_set_env("PWD", cd->curpath);
	}
	else
	{
		ft_memset((void*)absolute_path, 0, sizeof(absolute_path));
		if (getcwd(absolute_path, sizeof(absolute_path)) != NULL && ft_getenv("PWD"))
			ft_cd_set_env("PWD", absolute_path);
	}
    if (is_root_dir(ft_getenv("PWD")))
		ft_cd_set_env("PWD", "/");
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