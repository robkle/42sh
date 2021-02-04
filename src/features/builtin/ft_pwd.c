/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihwang <ihwang@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/14 10:22:48 by dthan             #+#    #+#             */
/*   Updated: 2021/02/04 15:41:23 by ihwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static void		integrate_options(t_opt *opt)
{
	opt->applied |= BUILTIN_PWD_OPT_L;
	if (opt->applied & BUILTIN_PWD_OPT_P && opt->applied & BUILTIN_PWD_OPT_L)
		opt->applied = BUILTIN_PWD_OPT_P;
}

int				ft_pwd(t_process *p)
{
	t_opt		opt;
	char		*pwd;
	int			free_flag;

	ft_cd_pwd_init_opt(&opt, BUILTIN_PWD_OPT_SET);
	ft_cd_pwd_check_builtin_opts(p->av, &opt);
	if (opt.applied == BUILTIN_INVALID_OPT)
	{
		ft_dprintf(2, "%s: pwd: %s: invalid option", SHELL_NAME, opt.invalid_opt);
		return (EXIT_FAILURE);
	}
	integrate_options(&opt);
	free_flag = 0;
	pwd = NULL;
	if (opt.applied == BUILTIN_PWD_OPT_P || (pwd = ft_getcwd_logical()) == NULL)
	{
		pwd = getcwd(NULL, 0);
		free_flag = 1;
	}
	ft_printf("%s\n", pwd);
	if (free_flag == 1)
		free(pwd);
	return (EXIT_SUCCESS);
}
