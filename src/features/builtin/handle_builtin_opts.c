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

#include "shell.h"

void		init_opt(t_opt *opt, const char *opt_set)
{
	ft_bzero(opt, sizeof(t_opt));
	opt->opt_set = opt_set;
	opt->opt_len = (char)ft_strlen(opt_set);
}


static void	add_option(t_opt *opt, char ch)
{
	int		i;

	i = 0;
	while (i < opt->opt_len)
	{
		if (ch == opt->opt_set[i])
		{
			opt->opt_apply |= 1 << i;
			return ;
		}
		++i;
	}
}

void		check_builtin_options(char **av, t_opt *opt)
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
				opt->opt_apply = BUILTIN_INVALID_OPT;
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

