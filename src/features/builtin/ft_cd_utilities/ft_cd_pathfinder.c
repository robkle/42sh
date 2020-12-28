/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd_pathfinder.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthan <dthan@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/06 15:04:58 by marvin            #+#    #+#             */
/*   Updated: 2020/12/27 17:35:47 by dthan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static void	set_oldpwd(char pwd[PATH_MAX])
{
	t_process	*cmd;

	if ((getcwd(pwd, PATH_MAX)) == NULL)
		return ;
	if ((cmd = (t_process*)ft_memalloc(sizeof(t_process))) == NULL)
		return ;
	if ((cmd->av = (char**)ft_memalloc(sizeof(char*) * 2)) == NULL)
		return ;
	cmd->av[0] = ft_strdup("setenv");
	cmd->av[1] = ft_strnew(7 + ft_strlen(pwd));
	cmd->av[1] = ft_strcpy(cmd->av[1], "OLDPWD=");
	cmd->av[1] = ft_strcat(cmd->av[1], pwd);
	cmd->ac = 2;
	ft_setenv(cmd);
	ft_strlst_del(&cmd->av, 2);
	free(cmd);
}

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
		(var_pwd = ft_getenv("PWD")) ? ft_strcpy(var_pwd, pwd) : 0;
	}
	ft_strlst_del(&split, i + 1);
}

static void cd_root(t_process *c)
{
    char    *old;
	char	pwd[PATH_MAX];
	char	*var_pwd;

    if ((old = ft_getenv("OLDPWD")))
		ft_strcpy(old, getcwd(pwd, PATH_MAX));
	else
		set_oldpwd(pwd);
   	ft_strcpy(pwd, c->av[1]);
	chdir(pwd);
	if ((var_pwd = ft_getenv("PWD")))
		ft_strcpy(var_pwd, pwd);
}

static void cd_not_root(t_process *c)
{
    char    *old;
	char	pwd[PATH_MAX];

    if ((old = ft_getenv("OLDPWD")))
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
