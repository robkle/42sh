/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthan <dthan@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/14 10:20:58 by dthan             #+#    #+#             */
/*   Updated: 2020/12/14 10:22:28 by dthan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int			ft_env(void)
{
	int		i;

	i = -1;
	while (g_shell.env[++i])
	{
		ft_putstr(g_shell.env[i]);
		ft_putstr("\n");
	}
	return (EXIT_SUCCESS);
}