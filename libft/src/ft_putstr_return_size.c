/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_return_size.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihwang <ihwang@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/27 14:54:08 by ihwang            #+#    #+#             */
/*   Updated: 2020/10/05 01:19:39 by ihwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

size_t		ft_putstr_return_size(char const *s)
{
	size_t	ret;

	ret = 0;
	while (*s)
	{
		write(1, s++, 1);
		++ret;
	}
	return (ret);
}
