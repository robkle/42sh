/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_setenv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihwang <ihwang@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/03 00:41:54 by ihwang            #+#    #+#             */
/*   Updated: 2021/03/21 11:16:58 by ihwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static void	add_env(char *arg)
{
	int		i;
	char	**temp;

	i = -1;
	while (g_shell.env[++i])
		NULL;
	temp = (char**)malloc(sizeof(char*) * (i + 2));
	i = -1;
	while (g_shell.env[++i])
		temp[i] = g_shell.env[i];
	temp[i] = (char*)malloc(sizeof(char) * PATH_MAX);
	ft_strcpy(temp[i], arg);
	temp[i + 1] = NULL;
	free(g_shell.env);
	g_shell.env = temp;
}

static void	ft_setenv_sub(char *arg)
{
	char	**split;
	char	*var;
	int		j;

	split = ft_strsplit(arg, '=');
	if ((var = ft_getenv(split[0])))
	{
		var++;
		j = 0;
		var[0] = '\0';
		while (split[++j])
			ft_strcat(var, split[j]);
	}
	else
		add_env(arg);
	j = -1;
	while (split[++j])
		NULL;
	ft_strlst_del(&split, j + 1);
}

int			ft_setenv(t_process *c)
{
	int		i;
	int		j;

	i = 0;
	while (++i < c->ac)
	{
		j = -1;
		while (ft_isalnum(c->av[i][++j]))
			NULL;
		if (c->av[i][j] == '\0')
			;
		else if (c->av[i][j] != '=' || j == 0)
		{
			ft_dprintf(2, "%s: setenv: '%s': not a valid identifier\n", \
			SHELL_NAME, c->av[i]);
			return (EXIT_FAILURE);
		}
		else
		{
			ft_setenv_sub(c->av[i]);
			return (EXIT_SUCCESS);
		}
	}
	return (EXIT_FAILURE);
}
