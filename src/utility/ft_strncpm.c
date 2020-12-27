/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncpm.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthan <dthan@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/01 00:58:13 by dthan             #+#    #+#             */
/*   Updated: 2020/11/01 01:00:49 by dthan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/utilities.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t i;

	i = 0;
	while ((s1[i] || s2[i]) && i < n)
	{
		if (s1[i] != s2[i])
			return ((unsigned char)(s1[i]) - (unsigned char)(s2[i]));
		i++;
	}
	return (0);
}
