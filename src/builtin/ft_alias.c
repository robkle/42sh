/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_alias.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgrankul <vgrankul@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/15 23:35:55 by vgrankul          #+#    #+#             */
/*   Updated: 2020/10/05 04:14:12 by vgrankul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void sort_alias_list(t_alias **aliaslist)
{
	int i;
	int j;
	t_alias *tmp;

	i = 0;
	while(aliaslist[i] != NULL)
	{
		j = i;
		while (aliaslist[j + 1] != NULL)
		{
			if (ft_strcmp(aliaslist[i]->name, aliaslist[j + 1]->name) > 0)
			{
				tmp = aliaslist[i];
				aliaslist[i] = aliaslist[j + 1];
				aliaslist[j + 1] = tmp;
			}
			j++;
		}
		i++;
	}
}

void print_all()
{
	int i;

	i = 0;
	while(g_alias[i] != NULL)
	{
		ft_printf("alias %s='%s'\n", g_alias[i]->name, g_alias[i]->value);
		i++;
	}
}

char	*set_value(char *argv)
{
	int		i;
	char	*value;

	i = 0;
	while (argv[i] != '\0' && argv[i] != '=')
		i++;
	value = ft_strsub(argv, i + 1, ft_strlen(argv) - (i + 1));
	return (value);
}

char	*set_name(char *argv)
{
	int		i;
	char	*name;

	i = 0;
	while (argv[i] != '\0' && argv[i] != '=')
		i++;
	name = ft_strsub(argv, 0, i);
	return (name);
}

int   add_alias(int count, char *alias, t_alias ***aliaslist)
{
	t_alias   **new;
	int     j;

	j = 0;
	if((new = (t_alias**)malloc(count * sizeof(t_alias*) + 1)))
	{
		while((*aliaslist)[j] != NULL)
		{
			if ((new[j] = (t_alias*)malloc(sizeof(t_alias))))
			{
				new[j]->name = ft_strdup((*aliaslist)[j]->name);
				new[j]->value = ft_strdup((*aliaslist)[j]->value);
			}
			j++;
		}
	}
	if((new[j] = (t_alias*)malloc(sizeof(t_alias))))
	{
		new[j]->name = set_name(alias);
		new[j]->value = set_value(alias);
		j++;
	}
	new[j] = NULL;
	sort_alias_list(new);
	free((*aliaslist));
	(*aliaslist) = new;
	return (0);
}

int set_alias(char *alias, t_alias ***aliaslist)
{
	int i;

	i = 0;
	while((*aliaslist)[i] != NULL)
	{
		if (ft_strncmp((*aliaslist)[i]->name, alias, ft_strlen((*aliaslist)[i]->name)) == 0)
		{
			free((*aliaslist)[i]->value);
			(*aliaslist)[i]->value = set_value(alias);
			return (0);
		}
		i++;
	}
	return(add_alias(i + 1, alias, aliaslist));
}

void print_alias(char *alias)
{
	int i;

	i = 0;
	while(g_alias[i] != NULL)
	{
		if (ft_strncmp(g_alias[i]->name, alias, ft_strlen(g_alias[i]->name)) == 0)
		{
			ft_printf("alias %s='%s'\n", g_alias[i]->name, g_alias[i]->value);
			return ;
		}
		i++;
	}
	ft_printf("42sh: alias: %s: not found\n", alias);
}

int ft_alias(t_process *c)
{
	int i;

	i = 1;
	ft_printf("ALIAS börjar\n");
	if (c->ac == 1)
		print_all();
	else
	{
		while(c->av[i] != NULL)
		{
			if (ft_strchr(c->av[i], '=') != NULL)
				set_alias(c->av[i], &g_alias);
			else
				print_alias(c->av[i]);
			i++; 
		} 
	}
	ft_printf("alias DONE\n");
	return (0);
}