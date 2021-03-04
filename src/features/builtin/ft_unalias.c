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
				return (0);
			}
			free(alias_name);
			i++;
		}
	}
	ft_printf("42sh: unalias: %s: not found\n", alias);
	return (1);
}

int		count_arr(void)
{
	int i;

	i = 0;
	if (g_shell.alias != NULL)
	{
		while (g_shell.alias[i] != NULL)
			i++;
	}
	return (i);
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

void	remove_all(t_alias ***aliaslist)
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
}

int		ft_unalias(t_process *c)
{
	int i;
	int status;
	int count;

	i = 1;
	status = 0;
	count = 0;
	if (c->ac == 1)
		ft_printf("unalias: usage: unalias [-a] name [name...]\n");
	else
	{
		while (c->av[i] != NULL)
		{
			if (ft_strcmp(c->av[i], "-a") == 0)
				remove_all(&g_shell.alias);
			else if (find_alias(c->av[i]) == 0)
			{
				count = count_arr() - 1;
				status = remove_alias(c->av[i], &g_shell.alias, count);
			}
			i++;
		}
	}
	return (status);
}
