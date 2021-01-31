/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_number_str.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthan <dthan@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/28 17:33:37 by dthan             #+#    #+#             */
/*   Updated: 2021/01/28 17:34:27 by dthan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	is_number_str(char *str)
{
	int i;

	i = -1;
	if (str == NULL)
		return (0);
	while (str[++i])
		if (!ft_isdigit(str[i]))
			return (0);
	return (1);
}
