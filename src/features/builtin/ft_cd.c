/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthan <dthan@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/01 20:06:49 by ihwang            #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2021/02/02 17:47:21 by ihwang           ###   ########.fr       */
=======
/*   Updated: 2020/12/27 17:25:49 by dthan            ###   ########.fr       */
>>>>>>> 5e5e5ca71f9dd1b4a60dcd8b4b25c2da857ba47e
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

<<<<<<< HEAD
/*
** Refer to the CD section in the POSIX standard document if you need to analyze this function
** link: https://pubs.opengroup.org/onlinepubs/9699919799/utilities/cd.html
*/

static char	basic_error_check(char **av, t_opt opt)
{
	char	status;

	status = 0;
	if (opt.applied == BUILTIN_INVALID_OPT)
		status = ft_dprintf(2, "%s: cd: %s: invalid option", SHELL_NAME, opt.invalid_opt);
	if (av[opt.operand_count + 2] != NULL)
		status = ft_dprintf(2, "%s: cd: too many arguments\n", SHELL_NAME);
	if (av[opt.operand_count + 1] == NULL && !ft_getenv("HOME")) //step1
		status = ft_dprintf(2, "%s cd: HOME not set\n", SHELL_NAME);
	return (status);	
}

static void	integrate_cd_options(t_opt *opt)
{
	opt->applied |= BUILTIN_CD_OPT_L;
	if (opt->applied & BUILTIN_CD_OPT_P && opt->applied & BUILTIN_CD_OPT_L)
		opt->applied = BUILTIN_CD_OPT_P;
}

static char	get_directory(t_process *c, t_cd *cd, t_opt *opt)
{
	if (c->av[opt->operand_count + 1] == NULL)
	{
		if ((ft_getenv("HOME") == NULL))
		{
			ft_dprintf(2, "%s: cd: HOME not set\n", SHELL_NAME);
			return (EXIT_FAILURE);
		}
		cd->directory = ft_getenv("HOME");
	}
	else if (ft_strequ(c->av[opt->operand_count + 1], "-"))
	{
		if ((ft_getenv("OLDPWD") == NULL))
		{
			ft_dprintf(2, "%s: cd: OLDPWD not set\n", SHELL_NAME);
			return (EXIT_FAILURE);
		}
		cd->print_info = TRUE;
		cd->directory = ft_getenv("OLDPWD");
	}
	else if (c->av[opt->operand_count + 1] != NULL)
		cd->directory = c->av[opt->operand_count + 1];
=======
static int	cd_no_arg(void)
{
	char	*var_pwd;
	char	pwd[PATH_MAX];
	char	*home;
	char	*old;

	if (!(home = get_var("HOME", g_shell.env, VAL)))
	{
		ft_putstr_fd("cd: HOME not set\n", STDERR_FILENO);
		return (EXIT_FAILURE);
	}
	if ((getcwd(pwd, PATH_MAX)) == NULL)
		return (EXIT_FAILURE);
	if ((old = get_var("OLDPWD", g_shell.env, VAL)))
		ft_strcpy(old, pwd);
	if ((var_pwd = get_var("PWD", g_shell.env, VAL)))
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
	if ((old = get_var("OLDPWD", g_shell.env, VAL)))
	{
		getcwd(pwd, PATH_MAX);
		ft_strcpy(temp, pwd);
		if ((var_pwd = get_var("PWD", g_shell.env, VAL)))
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
>>>>>>> 5e5e5ca71f9dd1b4a60dcd8b4b25c2da857ba47e
	return (EXIT_SUCCESS);
}

int			ft_cd(t_process *c)
{
<<<<<<< HEAD
	t_opt	opt;
	t_cd	cd;

	ft_memset(&cd, 0, sizeof(t_cd));
	ft_cd_pwd_init_opt(&opt, BUILTIN_CD_OPT_SET);
	ft_cd_pwd_check_builtin_opts(c->av, &opt);
	if (basic_error_check(c->av, opt) != 0)
		return (EXIT_FAILURE);
	integrate_cd_options(&opt);
	cd.opt = opt;
	if (get_directory(c, &cd, &opt) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (*(cd.directory) == '/') // step3
	{
		cd.curpath = ft_strdup(cd.directory);
		return (ft_cd_append_slash_to_curpath(&cd));
	}
	else if (ft_strnstr(cd.directory, "..", 2) || ft_strnstr(cd.directory, ".", 1)) //step4
		return (ft_cd_get_curpath_from_dir(&cd));
	else
		return (ft_cd_search_cdpath(&cd));
=======
	if (c->ac == 1)
		return (cd_no_arg());
	else if (ft_strequ(c->av[1], "-"))
		return (cd_exchange());
	else
		return (ft_cd_pathfinder(c));
>>>>>>> 5e5e5ca71f9dd1b4a60dcd8b4b25c2da857ba47e
}
