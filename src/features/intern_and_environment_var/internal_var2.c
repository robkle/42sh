/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   internal_val2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthan <dthan@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/27 12:46:20 by dthan             #+#    #+#             */
/*   Updated: 2021/01/27 12:48:53 by dthan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	clear_intern_var(t_var *intern_var)
{
	if (intern_var)
	{
		(intern_var->name) ? free(intern_var->name) : 0;
		(intern_var->value) ? free(intern_var->value) : 0;
		free(intern_var);
	}
}

void	clean_table_intern_var(t_var **table)
{
	int i;

	i = -1;
	if (table)
	{
		while (table[++i])
			clear_intern_var(table[i]);
		free(table);
	}
}

int		count_intern_var_table(t_var **table)
{
	int ct;
	int i;

	ct = 0;
	i = -1;
	while (table[++i])
		ct++;
	return (ct);
}

int		is_intern_var(char *name)
{
	int i;

	if (name == NULL)
		return (0);
	i = -1;
	while (g_shell.intern_var[++i])
		if (ft_strequ(name, g_shell.intern_var[i]->name))
			return (1);
	return (0);
}
