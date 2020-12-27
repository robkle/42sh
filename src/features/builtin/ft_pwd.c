/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthan <dthan@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/14 10:22:48 by dthan             #+#    #+#             */
/*   Updated: 2020/12/25 17:54:17 by dthan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int ft_pwd()
{
	char	pwd[PATH_MAX];

	if ((getcwd(pwd, PATH_MAX)) == NULL)
		return (EXIT_FAILURE);
	ft_putstr(pwd);
	ft_putstr("\n");
	return (EXIT_SUCCESS);
}