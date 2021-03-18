/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthan <dthan@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/14 10:20:58 by dthan             #+#    #+#             */
/*   Updated: 2021/03/18 19:53:17 by dthan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int			ft_env(void)
{
	int		i;

	i = -1;
	if (fcntl(STDOUT_FILENO, F_GETFD) == -1)
	{
		ft_dprintf(2, "%s: env: Write error: Bad file descriptor\n",
			SHELL_NAME);
		return (1);
	}
	while (g_shell.env[++i])
		ft_printf("%s\n", g_shell.env[i]);
	return (EXIT_SUCCESS);
}
