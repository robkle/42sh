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

void	print_all(t_alias **alias)
{
	int i;

	i = 0;
	while (alias[i] != NULL)
	{
		ft_printf("alias %s='%s'\n", alias[i]->name, alias[i]->value);
		i++;
	}
}

int		add_alias(int count, char *alias, t_alias ***aliaslist)
{
	t_alias	**new;
	int		j;

	j = 0;
	if ((new = (t_alias**)malloc(count * sizeof(t_alias*) + 1)))
	{
		while ((*aliaslist)[j] != NULL)
		{
			if (!(new[j] = (t_alias*)malloc(sizeof(t_alias))))
				return (-1);
			new[j]->name = ft_strdup((*aliaslist)[j]->name);
			new[j]->value = ft_strdup((*aliaslist)[j]->value);
			j++;
		}
	}
	if (!(new[j] = (t_alias*)malloc(sizeof(t_alias))))
		return (-1);
	new[j]->name = set_name(alias);
	new[j]->value = set_value(alias);
	j++;
	new[j] = NULL;
	sort_alias_list(new);
	free((*aliaslist));
	(*aliaslist) = new;
	return (0);
}

int		set_alias(char *alias, t_alias ***aliaslist)
{
	int		i;
	char	*alias_name;

	i = 0;
	alias_name = set_name(alias);
	if (is_valid_alias_name(alias_name) != 0)
		return (-1);
	while ((*aliaslist)[i] != NULL)
	{
		if (ft_strcmp((*aliaslist)[i]->name,
		(alias_name = set_name(alias))) == 0)
		{
			free(alias_name);
			free((*aliaslist)[i]->value);
			(*aliaslist)[i]->value = set_value(alias);
			return (0);
		}
		free(alias_name);
		i++;
	}
	return (add_alias(i + 1, alias, aliaslist));
}

void	print_alias(char *alias)
{
	int i;

	i = 0;
	while (g_shell.alias[i] != NULL)
	{
		if (ft_strcmp(g_shell.alias[i]->name, alias) == 0)
		{
			ft_printf("alias %s='%s'\n", g_shell.alias[i]->name,
				g_shell.alias[i]->value);
			return ;
		}
		i++;
	}
	ft_printf("42sh: alias: %s: not found\n", alias);
}

int		ft_alias(t_process *c)
{
	int i;
	int status;

	i = 1;
	status = 0;
	if (c->ac == 1)
		print_all(g_shell.alias);
	else
	{
		while (c->av[i] != NULL)
		{
			if (ft_strcmp(c->av[i], "-p") == 0)
				print_all(g_shell.alias);
			else if (ft_strchr(c->av[i], '=') != NULL)
				status = set_alias(c->av[i], &g_shell.alias);
			else
				print_alias(c->av[i]);
			i++;
		}
	}
	return (status);
}
