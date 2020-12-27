/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthan <dthan@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/18 10:41:55 by ihwang            #+#    #+#             */
/*   Updated: 2020/12/16 10:32:08 by dthan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"
#include <stdio.h>

void					*ft_memcpy(void *dst, const void *src, size_t n)
{
	unsigned char		*pt_dst;
	const unsigned char	*pt_src;

	pt_dst = dst;
	pt_src = src;
	while (n-- > 0)
		*(pt_dst++) = *(pt_src++);
	return ((void*)dst);
}
