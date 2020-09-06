/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihwang <ihwang@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/06 15:27:24 by ihwang            #+#    #+#             */
/*   Updated: 2020/09/06 15:19:50 by ihwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int			ft_env(void)
{
	int		i;

	i = -1;
	while (g_env[++i])
	{
		ft_putstr(g_env[i]);
		ft_putstr("\n");
	}
	return (EXIT_SUCCESS);
}

int			ft_pwd(void)
{
	char	pwd[PATH_MAX];

	if ((getcwd(pwd, PATH_MAX)) == NULL)
		return (EXIT_FAILURE);
	ft_putstr(pwd);
	ft_putstr("\n");
	return (EXIT_SUCCESS);
}

int			ft_exit(int opt)
{
	int		i;

	i = -1;
	delete_save_history(&g_h);
	while (g_env[++i])
		ft_strdel(&g_env[i]);
	ft_strdel(&g_env[i]);
	free(g_env);
	exit(opt);
	return (EXIT_FAILURE);
}

int			ft_echo(t_exe *c)
{
	int		i;

	i = 0;
	while (++i < c->ac)
	{
		ft_putstr(c->av[i]);
		if (i + 1 != c->ac && ft_strcmp(c->av[i], ""))
			ft_putstr(" ");
	}
	ft_putchar('\n');
	return (EXIT_SUCCESS);
}
