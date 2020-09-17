/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihwang <ihwang@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/01 20:06:49 by ihwang            #+#    #+#             */
/*   Updated: 2020/09/15 22:05:00 by ihwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static char *cd_no_arg(void)
{
	char	*var_pwd;
	char	pwd[PATH_MAX];
	char	*home;
	char	*old;

	if (!(home = get_var("HOME", g_env, VAL)))
		return (ft_strdup("42sh: cd: Home not set\n"));
	getcwd(pwd, PATH_MAX);
	if ((old = get_var("OLDPWD", g_env, VAL)))
		ft_strcpy(old, pwd);
	if ((var_pwd = get_var("PWD", g_env, VAL)))
		ft_strcpy(pwd, home);
	chdir(home);
	return (ft_strdup("success"));
}

static char	*cd_exchange(void)
{
	char	pwd[PATH_MAX];
	char	*old;
	char	*var_pwd;
	char	*temp;

	temp = (char*)malloc(PATH_MAX);
	temp[0] = '\0';
	if ((old = get_var("OLDPWD", g_env, VAL)))
	{
		getcwd(pwd, PATH_MAX);
		ft_strcpy(temp, pwd);
		if ((var_pwd = get_var("PWD", g_env, VAL)))
			ft_strcpy(var_pwd, old);
		ft_strcpy(pwd, old);
		chdir(pwd);
		ft_strcpy(old, temp);
	}
	else
		return (ft_strdup("cd: OLDPWD not set \n"));
	ft_strdel(&temp);
	return (ft_strdup("success"));
}

char		*ft_cd(t_exe *c)
{
	if (c->ac == 1)
		return (cd_no_arg());
	else if (ft_strequ(c->av[1], "-"))
		return (cd_exchange());
	else
		return (ft_cd_pathfinder(c));
}
