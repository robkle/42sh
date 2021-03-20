/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atolli_check.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihwang <ihwang@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/20 01:55:34 by ihwang            #+#    #+#             */
/*   Updated: 2021/03/20 03:05:48 by ihwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

/*
**	The variable 'stat' is for checking whether 'str' is in range of long long.
*/

long long	ft_atolli_check(const char *str, char *stat)
{
	unsigned long long	res;
	int	neg;
	
	neg = 1;
	res = 0;
	while (*str && (*str == ' ' || *str == '\n' || *str == '\t' ||
				*str == '\v' || *str == '\f' || *str == '\r'))
		++str;
	if (*str == '-')
		neg = -1;
	if (*str == '-' || *str == '+')
		++str;
	while (*str && *str >= '0' && *str <= '9')
	{
		res = res * 10 + (*str - 48);
		++str;
		if ((neg == 1 && res > (unsigned long long)LLONG_MAX) \
		|| (neg == -1 && res > (unsigned long long)LLONG_MAX + 1))
		{
			*stat = 0;
			return (0);
		}
	}
	*stat = 1;
	return ((long long)res * neg);
}