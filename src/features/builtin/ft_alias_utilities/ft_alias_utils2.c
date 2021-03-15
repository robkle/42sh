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

void	set_aliastable(void)
{
	g_shell.alias = (t_alias**)malloc(sizeof(t_alias*) + 1);
	g_shell.alias[0] = NULL;
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

int		print_all(void)
{
	int i;

	i = 0;
	if (fcntl(STDOUT_FILENO, F_GETFD) != -1)
	{
		if (g_shell.alias != NULL)
		{
			while (g_shell.alias[i] != NULL)
			{
				ft_printf("alias %s='%s'\n", g_shell.alias[i]->name,
				g_shell.alias[i]->value);
				i++;
			}
		}
	}
	else
	{
		ft_dprintf(2, "%s: alias: Write error: Bad file descriptor\n",
			SHELL_NAME);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
