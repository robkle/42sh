/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihwang <ihwang@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/01 20:06:49 by ihwang            #+#    #+#             */
/*   Updated: 2021/03/21 11:19:16 by ihwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static char	basic_error_check(char **av, t_opt opt)
{
	char	status;

	status = 0;
	if (opt.applied == BUILTIN_INVALID_OPT)
		status = ft_dprintf(2, "%s: cd: %c: invalid option\n", \
		SHELL_NAME, opt.invalid_opt);
	if (av[opt.operand_count + 2] != NULL)
		status = ft_dprintf(2, "%s: cd: too many arguments\n", SHELL_NAME);
	if (av[opt.operand_count + 1] == NULL && !ft_getenv("HOME"))
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
	if (*(cd.directory) == '/')
	{
		cd.curpath = ft_strdup(cd.directory);
		return (ft_cd_append_slash_to_curpath(&cd));
	}
	else if (ft_strnstr(cd.directory, "..", 2) || \
	ft_strnstr(cd.directory, ".", 1))
		return (ft_cd_get_curpath_from_dir(&cd));
	else
		return (ft_cd_search_cdpath(&cd));
}
