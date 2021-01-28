/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment_var.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthan <dthan@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/12 22:11:11 by dthan             #+#    #+#             */
/*   Updated: 2021/01/27 12:27:27 by dthan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

char	**set_env(char **sample)
{
	char	**env;
	int		i;

	i = -1;
	while (sample[++i])
		NULL;
	env = (char**)ft_memalloc(sizeof(char*) * (i + 1));
	i = -1;
	while (sample[++i])
	{
		env[i] = (char*)ft_memalloc(sizeof(char) * PATH_MAX);
		ft_strcpy(env[i], sample[i]);
	}
	env[i] = NULL;
	return (env);
}

int		is_eligible_to_export_to_env(t_var var)
{
	if (var.name && var.value && var.exported)
		return (1);
	return (0);
}

void	update_environment_var(char *name, char *value)
{
	int		i;
	char	*str;
	int		len;

	i = -1;
	str = NULL;
	len = ft_strlen(name);
	while (g_shell.env[++i])
	{
		if (ft_strnequ(g_shell.env[i], name, len) && g_shell.env[i][len] == '=')
		{
			ft_strcpy(g_shell.env[i], name);
			ft_strcat(g_shell.env[i], "=");
			ft_strcat(g_shell.env[i], value);
			break ;
		}
	}
}

void	add_environment_var(char *name, char *value)
{
	char	**new_table;
	int		size;
	int		i;

	if (!name || !value)
		return ;
	size = ft_arraylen(g_shell.env) + 2;
	new_table = (char**)ft_memalloc(sizeof(char*) * size);
	i = -1;
	while (g_shell.env[++i])
		new_table[i] = g_shell.env[i];
	new_table[i] = ft_strbuilder(3, new_table[i], name, "=", value);
	new_table[i + 1] = NULL;
	free(g_shell.env);
	g_shell.env = new_table;
}

void	add_update_environment_var(char *name, char *value)
{
	if (ft_getenv(name))
		update_environment_var(name, value);
	else
		add_environment_var(name, value);
}

void	delete_environment_var(char *name)
{
	char	**new_table;
	int		i;
	int		j;
	int		len;

	if (!name || ft_arraylen(g_shell.env) == 0)
		return ;
	new_table = (char**)ft_memalloc(sizeof(char*) * ft_arraylen(g_shell.env));
	i = -1;
	j = 0;
	len = ft_strlen(name);
	while (g_shell.env[++i])
	{
		if (ft_strnequ(g_shell.env[i], name, len) && g_shell.env[i][len] == '=')
		{
			free(g_shell.env[i]);
			continue;
		}
		new_table[j++] = g_shell.env[i];
	}
	new_table[j] = NULL;
	free(g_shell.env);
	g_shell.env = new_table;
}
