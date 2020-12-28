/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_prompt.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthan <dthan@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/02 15:30:45 by tango             #+#    #+#             */
/*   Updated: 2020/12/27 17:25:20 by dthan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static size_t	print_42sh_usr(void)
{
	char 		*usr;
	size_t		ret;

	ret = 0;
	ft_putstr(PMPT_MGTA);
	ft_putstr(PMPT_BOLD);
	ret += ft_printf("%s ", SHELL_NAME);
	ft_putstr(PMPT_INIT);
	if ((usr = ft_getenv("USER")))
	{
		ft_putstr(PMPT_SKYB);
		ret += ft_printf(usr);
	}
	ret += ft_printf(" ");
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
	ret += ft_printf("[");
	if ((home = ft_getenv("HOME")))
	{
		if (!ft_strcmp(pwd, home))
			ret += ft_printf("%s", pwd);
		else if (ft_strstr(pwd, home))
		{
			ret += ft_printf("~");
			ret += ft_printf("%s", ft_strstr_e(pwd, home));
		}
		else
			ret += ft_printf("%s", pwd);
	}
	else
		ret += ft_printf("%s", pwd);
	ret += ft_printf("]");
	return (ret);
}

size_t			get_prompt(void)
{
	size_t		ret;

	ret = print_42sh_usr();
	ret += print_cwd();
	ft_putstr(PMPT_INIT);
	ret += ft_printf("\n> ");
	return (ret);
}
