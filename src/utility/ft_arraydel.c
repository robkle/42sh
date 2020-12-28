/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_arraydel.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthan <dthan@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/04 06:29:33 by dthan             #+#    #+#             */
/*   Updated: 2020/12/25 19:02:29 by dthan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	ft_arraydel(char **string_array)
{
	char *ptr;
	char **tmp;

	if (!string_array)
		return ;
	tmp = string_array;
	while (*string_array)
	{
		ptr = *string_array;
		string_array++;
		free(ptr);
	}
	free(tmp);
}
