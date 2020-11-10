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
	// the list should be sorted also.
	t_alias   **new;
	int     j;

	j = 0;
	if((new = (t_alias**)malloc(count * sizeof(t_alias*) + 1)))
	{
		while((*aliaslist)[j] != NULL)
		{
			new[j] = (t_alias*)malloc(sizeof(t_alias)); // check if fail
			new[j]->name = ft_strdup((*aliaslist)[j]->name);
			new[j]->value = ft_strdup((*aliaslist)[j]->value);
			   j++;
		}
	}
	new[j] = (t_alias*)malloc(sizeof(t_alias)); // check if fail
	new[j]->name = set_name(alias);
	new[j]->value = set_value(alias);
	j++;
	new[j] = NULL;
	free((*aliaslist));
	(*aliaslist) = new;
	return (0);
}

int		a_strchr(char *str, int c)
{
	int i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == c)
			return (1);
		i++;
	} 
	return (0);
}

int set_alias(char *alias, t_alias ***aliaslist)
{
	int i;

	i = 0;
	while ((*aliaslist)[i] != NULL)
	{
		ft_printf("%s %s\n", (*aliaslist)[i]->name,(*aliaslist)[i]->value);
		i++;
	}
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
	while(g_shell.alias[i] != NULL)
	{
		if (ft_strncmp(g_shell.alias[i]->name, alias, ft_strlen(g_shell.alias[i]->name)) == 0)
			ft_printf("alias %s'%s'\n", g_shell.alias[i]->name, g_shell.alias[i]->value);
		i++;
	}
	ft_printf("42sh: alias: %s: not found", alias);
}

void print_all()
{
	int i;

	i = 0;
	while(g_shell.alias[i] != NULL)
	{
		ft_printf("alias %s'%s'\n", g_shell.alias[i]->name, g_shell.alias[i]->value);
		i++;
	}  // bövs den läggas till NUll i något skede, finns någon sådan funktion, initialize i ft_alias ifall det inte finns
}

int ft_alias(t_process *c)
{
	int i;

	i = 1;
	g_shell.alias = (t_alias**)malloc(sizeof(t_alias*));
	if (c->ac == 0)
		print_all();
	else
	{
		while(c->av[i] != NULL)
		{
			if (ft_strchr(c->av[i], '=') != NULL)
				set_alias(c->av[i], &g_shell.alias);
			else
				print_alias(c->av[i]);
			i++; 
		} 
	}
	i = 0;
	while(g_shell.alias[i] != NULL)
	{
		ft_printf("heres%s %s\n", g_shell.alias[i]->name, g_shell.alias[i]->value);
		i++;
	}
	return (0);
}