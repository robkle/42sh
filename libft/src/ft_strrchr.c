/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihwang <ihwang@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/22 15:05:37 by ihwang            #+#    #+#             */
/*   Updated: 2020/10/10 18:11:19 by ihwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	const char *pt_s;

	pt_s = s;
	while (*pt_s != '\0')
		pt_s++;
	while (pt_s != s - 1)
	{
		if (*pt_s == c)
			return ((char*)pt_s);
		pt_s--;
	}
	return (NULL);
}
