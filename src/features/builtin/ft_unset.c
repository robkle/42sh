/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthan <dthan@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/15 10:51:57 by dthan             #+#    #+#             */
/*   Updated: 2021/03/12 22:58:31 by dthan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int	ft_unset(int ac, char **av)
{
	int i;

	(void)ac;
	i = 0;
	while (av[++i])
		if (is_intern_var(av[i]))
			delete_intern_var(av[i]);
	return (EXIT_SUCCESS);
}
