/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_type.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihwang <ihwang@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/03 14:56:26 by ihwang            #+#    #+#             */
/*   Updated: 2021/02/03 18:15:32 by ihwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

/*
** 1. alias
** 2. builtin
** 3. path
*/

static int	look_for_alias(char *arg, char **alias)
{
	int i;

	i = -1;
	if (g_shell.alias != NULL)
	{
		while (g_shell.alias[++i])
		{
			if (ft_strequ(arg, g_shell.alias[i]->name))
			{
				*alias = g_shell.alias[i]->value;
				return (EXIT_SUCCESS);
			}
		}
	}
	return (EXIT_FAILURE);
}

static int	look_for_builtin(char *arg)
{
	t_builtin	*node;

	if (g_shell.builtins == NULL)
		return (EXIT_FAILURE);
	node = g_shell.builtins;
	while (node)
	{
		if (ft_strequ(arg, node->name))
			return (EXIT_SUCCESS);
		node = node->next;
	}
	return (EXIT_FAILURE);
}

static char	*get_full_path(char *arg, char **split)
{
	int		i;
	char	*full_path;

	i = -1;
	while (split[++i])
	{
		full_path = ft_strdup(split[i]);
		if (full_path[ft_strlen(full_path) - 1] != '/')
			full_path = ft_strjoin_and_free_string1(full_path, "/");
		full_path = ft_strjoin_and_free_string1(full_path, arg);
		if (access(full_path, F_OK) == 0)
			return (full_path);
		ft_strdel(&full_path);
	}
	return (NULL);
}

static int	look_for_path(char *arg, char **path)
{
	char	**split;
	int		split_count;
	char	*var;

	if ((var = ft_getenv("PATH")) == NULL)
		return (EXIT_FAILURE);
	if ((split = ft_strsplit(var, ':'))[0] == NULL)
	{
		free(split);
		return (EXIT_FAILURE);
	}
	*path = get_full_path(arg, split);
	split_count = -1;
	while (split[++split_count])
		NULL ;
	ft_strlst_del(&split, split_count);
	if (*path)
		return (EXIT_SUCCESS);
	return (EXIT_FAILURE);
}

int			ft_type(t_process *c)
{
	int		ret_code;
	char	*alias;
	char	*path;
	int		i;

	if (c->ac == 1)
		return (EXIT_SUCCESS);
	i = 0;
	path = NULL;
	alias = NULL;
	while (++i < c->ac)
	{
		if ((ret_code = look_for_alias(c->av[i], &alias)) == EXIT_SUCCESS)
			ft_printf("%s is aliased to `%s'\n", c->av[i], alias);
		else if ((ret_code = look_for_builtin(c->av[i])) == EXIT_SUCCESS)
			ft_printf("%s is a shell builtin\n", c->av[i]);
		else if ((ret_code = look_for_path(c->av[i], &path)) == EXIT_SUCCESS)
			ft_printf("%s is %s\n", c->av[i], path);
		else
			ft_dprintf(STDERR_FILENO, "%s: type: %s: not found\n", SHELL_NAME, c->av[i]);
		ft_strdel(&path);
		alias = NULL;
	}
	return (ret_code);
}