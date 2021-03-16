/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hash.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgrankul <vgrankul@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/15 23:35:55 by vgrankul          #+#    #+#             */
/*   Updated: 2020/12/26 11:43:35 by vgrankul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int		exists_in_hashtable(char *name, char *path, int index)
{
	t_hash *tmp;

	tmp = g_shell.hashtable[index];
	while (tmp != NULL)
	{
		if (ft_strcmp(tmp->name, name) == 0)
		{
			free(tmp->path);
			tmp->path = ft_strdup(path);
			tmp->hits = 0;
			return (0);
		}
		tmp = tmp->next;
	}
	return (1);
}
