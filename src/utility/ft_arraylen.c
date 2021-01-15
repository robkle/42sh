/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_arraylen.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthan <dthan@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/11 21:42:53 by dthan             #+#    #+#             */
/*   Updated: 2021/01/11 21:43:08 by dthan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int ft_arraylen(char **array)
{
	int ct;
	int i;

	ct = 0;
	i = -1;
	if (array == NULL)
		return (ct);
	while (array[++i])
		ct++;
	return (ct);
}
