/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unalias.c                                         :+:      :+:    :+: */
/*                                                    +:+ +:+         +:+     */
/*   By: vgrankul <vgrankul@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/15 23:35:55 by vgrankul          #+#    #+#             */
/*   Updated: 2020/10/05 04:14:12 by vgrankul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int		count_arr()
{
	int i;

	i = 0;
	while (g_alias[i] != NULL)
		i++;
	return (i);
}

void remove_alias(char *alias, t_alias ***aliaslist)
{
	t_alias   **new;
	int     j;
    int     i;
    int     count;

	j = 0;
    i = 0;
    count = count_arr() - 1;
	if((new = (t_alias**)malloc(count * sizeof(t_alias*) + 1)))
	{
		while(j < count)
		{
            if (ft_strcmp((*aliaslist)[i]->name, alias) == 0)
                i++;
			if ((new[j] = (t_alias*)malloc(sizeof(t_alias))))
			{
				new[j]->name = ft_strdup((*aliaslist)[i]->name);
				new[j]->value = ft_strdup((*aliaslist)[i]->value);
			}
			j++;
            i++;
		}
	}
	new[j] = NULL;
	free((*aliaslist));
    (*aliaslist) = new;
}

void remove_all(t_alias ***aliaslist)
{
    int i;

    i = 0;
    while((*aliaslist)[i] != NULL)
    {
        free((*aliaslist)[i]->name);
        free((*aliaslist)[i]->value);
        free((*aliaslist)[i]);
        i++;
    }
    //free((*aliaslist));
}

int ft_unalias(t_process *c)
{
    int i;

	i = 1;
	if (c->ac == 1)
		ft_printf("unalias: usage: unalias [-a] name [name...]\n");
	else
	{
		while(c->av[i] != NULL)
		{
			if (ft_strcmp(c->av[i], "-a") == 0)
				remove_all(&g_alias);
            else
				remove_alias(c->av[i], &g_alias);
			i++; 
		} 
	}
	return (0);
}