/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_setenv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihwang <ihwang@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/03 00:41:54 by ihwang            #+#    #+#             */
/*   Updated: 2020/09/11 17:49:02 by ihwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

char		**add_env(char *arg, char **env_list)
{
	int		i;
	char	**temp;

	i = -1;
	while (env_list[++i])
		NULL;
	temp = (char**)malloc(sizeof(char*) * (i + 2));
	i = -1;
	while (env_list[++i])
		temp[i] = env_list[i];
	temp[i] = (char*)malloc(sizeof(char) * PATH_MAX);
	ft_strcpy(temp[i], arg);
	temp[i + 1] = NULL;
	free(env_list);
	env_list = temp;
	return (env_list);
}

static void	ft_setenv_sub(char *arg)
{
	char	**split;
	char	*var;
	int		j;

	split = ft_strsplit(arg, '=');
	if ((var = get_var(split[0], g_env, VAL)))
	{
		var++;
		j = 0;
		var[0] = '\0';
		while (split[++j])
			ft_strcat(var, split[j]);
	}
	else
		g_env = add_env(arg, g_env);
	j = -1;
	while (split[++j])
		NULL;
	ft_strlst_del(&split, j + 1);
}

int			ft_setenv(t_exe *c)
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
			error_monitor("setenv: '", c->av[i],\
			"'; not a valid identifier", 1);
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
