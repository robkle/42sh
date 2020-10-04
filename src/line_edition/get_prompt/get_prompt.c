/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_prompt.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihwang <ihwang@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/02 15:30:45 by tango             #+#    #+#             */
/*   Updated: 2020/10/05 00:45:56 by ihwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_prompt.h"

static size_t	print_42sh_usr(void)
{
	char 		*usr;
	size_t		ret;

	ret = 0;
	ft_putstr(PMPT_MGTA);
	ft_putstr(PMPT_BOLD);
	ret += ft_putstr_return_size("42sh ");
	ft_putstr(PMPT_INIT);
	if ((usr = get_var("USER", g_env, VAL)))
	{
		ft_putstr(PMPT_SKYB);
		ret += ft_putstr_return_size(usr);
	}
	ret += ft_putstr_return_size(" ");
	return (ret);
}

static size_t	print_cwd(void)
{
	char 		pwd[PATH_MAX];
	char 		*home;
	size_t		ret;

	getcwd(pwd, PATH_MAX);
	ft_putstr(PMPT_YELW);
	ret = 0;
	ret += ft_putstr_return_size("[");
	if ((home = get_var("HOME", g_env, VAL)))
	{
		if (!ft_strcmp(pwd, home))
			ret += ft_putstr_return_size(pwd);
		else if (ft_strstr(pwd, home))
		{
			ret += ft_putstr_return_size("~");
			ret += ft_putstr_return_size(ft_strstr_e(pwd, home));
		}
		else
			ret += ft_putstr_return_size(pwd);
	}
	else
		ret += ft_putstr_return_size(pwd);
	ret += ft_putstr_return_size("]");
	return (ret);
}

size_t			get_prompt(void)
{
	size_t		ret;

	ret = print_42sh_usr();
	ret += print_cwd();
	ft_putstr(PMPT_INIT);
	ret += ft_putstr_return_size("\n> ");
	return (ret);
}
