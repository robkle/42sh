/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_alias_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthan <dthan@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/15 23:35:55 by vgrankul          #+#    #+#             */
/*   Updated: 2020/12/26 11:44:01 by dthan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int		is_valid_alias_char(int c)
{
	if (c == '/' || c == '$' || c == '`' || c == '=' || c == '"' || c == '\''
	|| c == '\\' || is_metacharacter(c) == 1)
	{
		return (0);
	}
	return (1);
}

int		is_valid_alias_name(char *alias)
{
	int		i;
	char	*alias_name;

	i = 0;
	alias_name = set_name(alias);
	if ((ft_strcmp(alias_name, "\0") == 0) || alias_name == NULL)
	{
		ft_dprintf(2, "42sh: alias: %s: not found\n", alias);
		free(alias_name);
		return (EXIT_FAILURE);
	}
	while (alias_name[i] != '\0')
	{
		if (is_valid_alias_char(alias_name[i]) != 1)
		{
			ft_dprintf(2, "42sh: alias: %s: invalid alias name\n", alias_name);
			free(alias_name);
			return (EXIT_FAILURE);
		}
		i++;
	}
	free(alias_name);
	return (EXIT_SUCCESS);
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

void	sort_alias_list(t_alias **aliaslist)
{
	int		i;
	int		j;
	t_alias	*tmp;

	i = 0;
	while (aliaslist[i] != NULL)
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
