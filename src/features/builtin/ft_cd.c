/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihwang <ihwang@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/01 20:06:49 by ihwang            #+#    #+#             */
/*   Updated: 2021/03/09 12:30:09 by rklein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

/*
** To whom may want to know about cd.
**
** The main parts of ft_cd function are stored in builtin/ft_cd_utilities directory.
** Their main logics are fully dedicated to the POSIX standard document.
** Look into the link down below if you need to investigate how it works.
**
** The behaviours of ft_cd are described in 10 steps by the document, and
** the steps from 1 to 4 are compressed and stored in
** 'int ft_cd(t_process *c)' function which is the starting point of this feature.
** I commented the rest of the steps in each file according to its step
** in the 'ft_cd_utilities' directory, so you can find them with running
** this command in the directory or its parent
** directories for instance,
**
** $ greb -Rl step5 .
**
** Replace the step number with what you want to refer to.
**
** link: https://pubs.opengroup.org/onlinepubs/9699919799/utilities/cd.html
*/

static char	basic_error_check(char **av, t_opt opt)
{
	char	status;

	status = 0;
	if (opt.applied == BUILTIN_INVALID_OPT)
		status = ft_dprintf(2, "%s: cd: %c: invalid option\n", SHELL_NAME, opt.invalid_opt);
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
	return (EXIT_SUCCESS);
}

int			ft_cd(t_process *c)
{
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
}
