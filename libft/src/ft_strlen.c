/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihwang <ihwang@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/22 15:00:44 by ihwang            #+#    #+#             */
/*   Updated: 2020/10/05 00:30:24 by ihwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

size_t	ft_strlen(const char *s)
{
	const char *pt_s;

	if (s == NULL)
		return (0);
	pt_s = s;
	while (*pt_s)
		pt_s++;
	return (pt_s - s);
}
