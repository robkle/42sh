/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_alias_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgrankul <vgrankul@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/15 23:35:55 by vgrankul          #+#    #+#             */
/*   Updated: 2020/10/05 04:14:12 by vgrankul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include "../includes/libft.h"

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
