/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd_pathfinder.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthan <dthan@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/06 15:04:58 by marvin            #+#    #+#             */
/*   Updated: 2020/09/30 04:55:11 by dthan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static void	cd_shaping_env(char *str)
{
	char	**split;
	char	pwd[PATH_MAX];
	char	*var_pwd;
	int		i;

	getcwd(pwd, PATH_MAX);
	split = ft_strsplit(str, '/');
	i = -1;
	while (split[++i])
	{
		if (!ft_strcmp(split[i], ".."))
			ft_strrchr(pwd, '/') != pwd ? (*ft_strrchr(pwd, '/') = '\0') :
				(*(ft_strrchr(pwd, '/') + 1) = '\0');
		else if (!ft_strcmp(split[i], "."))
			NULL;
		else
		{
			if (!(pwd[0] == '/' && pwd[1] == '\0'))
				ft_strcat(pwd, "/");
			ft_strcat(pwd, split[i]);
		}
		chdir(pwd);
		(var_pwd = get_env("PWD=", VAL)) ? ft_strcpy(var_pwd, pwd) : 0;
	}
	ft_strlst_del(&split, i + 1);
}

static void cd_root(t_process *c)
{
    char    *old;
	char	pwd[PATH_MAX];
	char	*var_pwd;

    if ((old = get_env("OLDPWD=", VAL)))
		ft_strcpy(old, getcwd(pwd, PATH_MAX));
	else
		set_oldpwd(pwd);
   	ft_strcpy(pwd, c->av[1]);
	chdir(pwd);
	if ((var_pwd = get_env("PWD=", VAL)))
		ft_strcpy(var_pwd, pwd);
}

static void cd_not_root(t_process *c)
{
    char    *old;
	char	pwd[PATH_MAX];

    if ((old = get_env("OLDPWD=", VAL)))
        old = ft_strcpy(old, getcwd(pwd, PATH_MAX));
    else
        set_oldpwd(pwd);
    cd_shaping_env(c->av[1]);
}

int     	ft_cd_pathfinder(t_process *c)
{
	if (possible_to_access_dir(c) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (c->av[1][0] == '/')
        cd_root(c);
	else
        cd_not_root(c);
	return (EXIT_SUCCESS);
}
