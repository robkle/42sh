/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_builtin_opts.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihwang <ihwang@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/28 17:43:34 by ihwang            #+#    #+#             */
/*   Updated: 2020/12/28 23:06:03 by ihwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** Builtin option handling interfaces
** 1. void init_opt(t_opt *opt, const char *opt_set);
** 2. check_builtin_opts(char **av, t_opt *opt);
*/

/*
** void init_opt(t_opt *opt, const char *opt_set);
** 
** Description
** init_opt initializes the t_opt struct with the given set of options.
** the second parameter *opt_set is a string made up of option chracters
** for a command you would like to implement
** (e.g. #define BUILTIN_CD_OPT_SET "PL", cd command has -P and -L options)
**
** Return value
** None
*/

/*
** void check_builtin_opts(char **av, t_opt *opt)
**
** Description
** check_builtin_opts takes 
**
**
*/

#include "shell.h"

void		init_opt(t_opt *opt, const char *opt_set)
{
	ft_bzero(opt, sizeof(t_opt));
	opt->opt_set = (char*)opt_set;
	opt->set_len = (char)ft_strlen(opt_set);
}


static void	add_option(t_opt *opt, char ch)
{
	int		i;

	i = 0;
	while (i < opt->set_len)
	{
		if (ch == opt->opt_set[i])
		{
			opt->applied |= 1 << i;
			return ;
		}
		++i;
	}
}

void		check_builtin_opts(char **av, t_opt *opt)
{
	int		i;
	int		j;
	int		arg_len;

	i = 1;
	while (av[i][0] == '-' && ft_strlen(av[i]) != 1)
	{
		opt->operand_count += 1;
		arg_len = ft_strlen(av[i]);
		j = 1;
		while (j < arg_len)
		{
			if (ft_strchr(opt->opt_set, av[i][j]) == NULL)
			{
				opt->applied = BUILTIN_INVALID_OPT;
				opt->invalid_opt = av[i][j];
				return ;
			}
			else
				add_option(opt, av[i][j]);
			++j;
		}
		++i;
	}
}
