/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd_pathfinder.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihwang <ihwang@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/06 15:04:58 by marvin            #+#    #+#             */
/*   Updated: 2020/09/24 03:09:42 by ihwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static char	*possible_to_access_dir(t_exe *c)
{
	t_stat		sb;
	char		*ret;

	stat(c->av[1], &sb);
	ret = ft_strdup("cd: ");
	ft_strjoin(ret, c->av[1]);
	if (access(c->av[1], F_OK))
		return (ft_strjoin(ret, ": No such file or directory\n"));
	else if ((sb.st_mode & F_TYPE_MASK) != S_IFDIR)
		return (ft_strjoin(ret, ": Not a directory\n"));
	else if (access(c->av[1], X_OK))
		return (ft_strjoin(ret, ": Permission denied\n"));
	ft_strdel(&ret);
	return (NULL);
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
		(var_pwd = get_var("PWD", g_env, VAL)) ? ft_strcpy(var_pwd, pwd) : 0;
	}
	ft_strlst_del(&split, i + 1);
}

static void cd_root(t_exe *c)
{
    char    *old;
	char	pwd[PATH_MAX];
	char	*var_pwd;

    if ((old = get_var("OLDPWD", g_env, VAL)))
		ft_strcpy(old, getcwd(pwd, PATH_MAX));
	else
		set_oldpwd(pwd);
   	ft_strcpy(pwd, c->av[1]);
	chdir(pwd);
	if ((var_pwd = get_var("PWD", g_env, VAL)))
		ft_strcpy(var_pwd, pwd);
}

static void cd_not_root(t_exe *c)
{
    char    *old;
	char	pwd[PATH_MAX];

    if ((old = get_var("OLDPWD", g_env, VAL)))
        old = ft_strcpy(old, getcwd(pwd, PATH_MAX));
    else
        set_oldpwd(pwd);
    cd_shaping_env(c->av[1]);
}

char     	*ft_cd_pathfinder(t_exe *c)
{
	char	*ret;
	if ((ret = possible_to_access_dir(c)))
		return (ret);
	if (c->av[1][0] == '/')
        cd_root(c);
	else
        cd_not_root(c);
	return (ft_strdup("success"));
}
