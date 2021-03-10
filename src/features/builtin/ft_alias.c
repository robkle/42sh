/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_alias.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthan <dthan@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/15 23:35:55 by vgrankul          #+#    #+#             */
/*   Updated: 2020/12/26 11:41:29 by dthan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int		add_alias(int count, char *alias, t_alias ***aliaslist)
{
	t_alias	**new;
	int		j;

	j = 0;
	if ((*aliaslist) != NULL &&
	(new = (t_alias**)malloc(count * sizeof(t_alias*) + 1)))
	{
		while ((*aliaslist)[j] != NULL)
		{
			if (!(new[j] = (t_alias*)malloc(sizeof(t_alias))))
				return (EXIT_FAILURE);
			new[j]->name = ft_strdup((*aliaslist)[j]->name);
			new[j]->value = ft_strdup((*aliaslist)[j]->value);
			j++;
		}
		if (!(new[j] = (t_alias*)malloc(sizeof(t_alias))))
			return (EXIT_FAILURE);
		new[j]->name = set_name(alias);
		new[j]->value = set_value(alias);
		new[++j] = NULL;
		sort_alias_list(new);
		remove_all(aliaslist);
		(*aliaslist) = new;
	}
	return (EXIT_SUCCESS);
}

int		set_alias(char *alias, t_alias ***aliaslist)
{
	int		i;
	char	*alias_name;

	i = 0;
	alias_name = NULL;
	if ((*aliaslist) != NULL)
	{
		while ((*aliaslist)[i] != NULL)
		{
			if (ft_strcmp((*aliaslist)[i]->name,
			(alias_name = set_name(alias))) == 0)
			{
				free(alias_name);
				free((*aliaslist)[i]->value);
				(*aliaslist)[i]->value = set_value(alias);
				return (EXIT_SUCCESS);
			}
			free(alias_name);
			i++;
		}
	}
	return (add_alias(i + 1, alias, aliaslist));
}

int		print_alias(char *alias)
{
	int i;

	i = 0;
	if (g_shell.alias != NULL)
	{
		while (g_shell.alias[i] != NULL)
		{
			if (ft_strcmp(g_shell.alias[i]->name, alias) == 0)
			{
				ft_printf("alias %s='%s'\n", g_shell.alias[i]->name,
					g_shell.alias[i]->value);
				return (EXIT_SUCCESS);
			}
			i++;
		}
	}
	ft_printf("42sh: alias: %s: not found\n", alias);
	return (EXIT_FAILURE);
}

int		alias_loop(t_process *c, int status)
{
	int i;
	int returnvalue;

	i = 0;
	returnvalue = 0;
	while (c->av[i] != NULL)
	{
		if (ft_strcmp(c->av[i], "-p") == 0)
			print_all();
		else if (ft_strchr(c->av[i], '=') != NULL)
		{
			if (is_valid_alias_name(c->av[i]) != 0)
				return (EXIT_FAILURE);
			if ((status = set_alias(c->av[i], &g_shell.alias)) > 0)
				returnvalue = status;
		}
		else
		{
			if ((status = print_alias(c->av[i])) > 0)
				returnvalue = status;
		}
		i++;
	}
	return (returnvalue);
}

int		ft_alias(t_process *c)
{
	int status;

	status = 0;
	if (g_shell.alias == NULL)
		set_aliastable();
	if (c->ac == 1)
		return (print_all());
	else if (c->ac > 1 && ft_strncmp(c->av[1], "-", 1) == 0)
	{
		if (ft_strcmp(c->av[1], "-p") == 0)
			return (print_all());
		else
		{
			ft_printf("42sh: alias: %s: invalid option\n", c->av[1]);
			ft_printf("alias: usage. alias [-p] [name[=value] ... ]\n");
			return (EXIT_FAILURE);
		}
	}
	status = alias_loop(c, status);
	return (status);
}
