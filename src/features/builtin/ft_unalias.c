/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unalias.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthan <dthan@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/15 23:35:55 by vgrankul          #+#    #+#             */
/*   Updated: 2021/01/06 01:10:30 by dthan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int		find_alias(char *alias)
{
	int		i;
	char	*alias_name;

	i = 0;
	if (g_shell.alias != NULL)
	{
		while (g_shell.alias[i] != NULL)
		{
			if (ft_strcmp(g_shell.alias[i]->name,
			(alias_name = set_name(alias))) == 0)
			{
				free(alias_name);
				return (EXIT_SUCCESS);
			}
			free(alias_name);
			i++;
		}
	}
	ft_printf("42sh: unalias: %s: not found\n", alias);
	return (EXIT_FAILURE);
}

int		remove_alias(char *alias, t_alias ***aliaslist, int count)
{
	t_alias	**new;
	char	*a_name;
	int		j;
	int		i;

	j = 0;
	i = 0;
	if (!(new = (t_alias**)malloc(count * sizeof(t_alias*) + 1)))
		return (EXIT_FAILURE);
	while (j < count)
	{
		if (ft_strcmp((*aliaslist)[i]->name, (a_name = set_name(alias))) == 0)
			i++;
		free(a_name);
		if (!(new[j] = (t_alias*)malloc(sizeof(t_alias))))
			return (EXIT_FAILURE);
		new[j]->name = ft_strdup((*aliaslist)[i]->name);
		new[j]->value = ft_strdup((*aliaslist)[i]->value);
		j++;
		i++;
	}
	new[j] = NULL;
	remove_all(aliaslist);
	(*aliaslist) = new;
	return (EXIT_SUCCESS);
}

int		remove_all(t_alias ***aliaslist)
{
	int i;

	i = 0;
	if ((*aliaslist != NULL))
	{
		while ((*aliaslist)[i] != NULL)
		{
			free((*aliaslist)[i]->name);
			free((*aliaslist)[i]->value);
			free((*aliaslist)[i]);
			i++;
		}
		free((*aliaslist));
		(*aliaslist) = NULL;
	}
	return (EXIT_SUCCESS);
}

int		unalias_loop(t_process *c)
{
	int i;
	int count;
	int status;
	int returnvalue;

	i = 1;
	count = 0;
	status = 0;
	returnvalue = 0;
	while (c->av[i] != NULL)
	{
		if (ft_strcmp(c->av[i], "-a") == 0)
			remove_all(&g_shell.alias);
		else if ((status = find_alias(c->av[i])) == 0)
		{
			count = count_arr() - 1;
			if ((status = remove_alias(c->av[i], &g_shell.alias, count)) > 0)
				returnvalue = status;
		}
		else
			returnvalue = status;
		i++;
	}
	return (returnvalue);
}

int		ft_unalias(t_process *c)
{
	int status;

	status = 0;
	if (c->ac == 1)
	{
		ft_printf("unalias: usage: unalias [-a] name [name...]\n");
		return (EXIT_FAILURE);
	}
	else if (c->ac > 1 && ft_strncmp(c->av[1], "-", 1) == 0)
	{
		if (ft_strcmp(c->av[1], "-a") == 0)
			return (remove_all(&g_shell.alias));
		else
		{
			ft_printf("42sh: unalias: %s: invalid option\n", c->av[1]);
			ft_printf("unalias: usage: unalias [-a] name [name...]\n");
			return (EXIT_FAILURE);
		}
	}
	status = unalias_loop(c);
	return (status);
}
