/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthan <dthan@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/01 20:06:49 by ihwang            #+#    #+#             */
/*   Updated: 2020/09/30 04:55:41 by dthan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static int	cd_no_arg(void)
{
	char	*var_pwd;
	char	pwd[PATH_MAX];
	char	*home;
	char	*old;

	if (!(home = get_env("HOME=", VAL)))
	{
		ft_putstr_fd("cd: HOME not set\n", STDERR_FILENO);
		return (EXIT_FAILURE);
	}
	if ((getcwd(pwd, PATH_MAX)) == NULL)
		return (EXIT_FAILURE);
	if ((old = get_env("OLDPWD=", VAL)))
		ft_strcpy(old, pwd);
	if ((var_pwd = get_env("PWD=", VAL)))
		ft_strcpy(pwd, home);
	if ((chdir(home)) == -1)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

static int	cd_exchange(void)
{
	char	pwd[PATH_MAX];
	char	*old;
	char	*var_pwd;
	char	*temp;

	if ((temp = (char*)malloc(PATH_MAX)) == NULL)
		return (EXIT_FAILURE);
	temp[0] = '\0';
	if ((old = get_env("OLDPWD=", VAL)))
	{
		getcwd(pwd, PATH_MAX);
		ft_strcpy(temp, pwd);
		if ((var_pwd = get_env("PWD=", VAL)))
			ft_strcpy(var_pwd, old);
		ft_strcpy(pwd, old);
		chdir(pwd);
		ft_strcpy(old, temp);
	}
	else
	{
		ft_putstr_fd("cd: OLDPWD not set\n", STDERR_FILENO);
		return (EXIT_FAILURE);
	}
	ft_strdel(&temp);
	return (EXIT_SUCCESS);
}

int			ft_cd(t_process *c)
{
	if (c->ac == 1)
		return (cd_no_arg());
	else if (ft_strequ(c->av[1], "-"))
		return (cd_exchange());
	else
		return (ft_cd_pathfinder(c));
}
