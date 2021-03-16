/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_set.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthan <dthan@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/09 03:36:20 by dthan             #+#    #+#             */
/*   Updated: 2021/03/12 22:57:54 by dthan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int	ft_set(void)
{
	int i;

	i = -1;
	while (g_shell.intern_var[++i])
		if (g_shell.intern_var[i]->name && g_shell.intern_var[i]->value)
			ft_printf("%s=%s\n",
				g_shell.intern_var[i]->name,
				g_shell.intern_var[i]->value);
	return (EXIT_SUCCESS);
}
