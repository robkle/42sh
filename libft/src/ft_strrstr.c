/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihwang <ihwang@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/22 15:06:21 by ihwang            #+#    #+#             */
/*   Updated: 2020/09/30 17:49:53 by ihwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strrstr(const char *haystack, const char *needle)
{
	int		i;
	size_t	haystack_len;
	size_t	needle_len;

	if (*needle == '\0')
		return ((char*)haystack);
	haystack_len = ft_strlen(haystack);
	needle_len = ft_strlen(needle);
	i = (int)haystack_len - (int)needle_len;
	if (i < 0)
		return (NULL);
	else if (i == 0)
		return ((char*)haystack);
	while (i >= 0)
	{
		if (ft_strnequ(&haystack[i], needle, needle_len))
			return ((char*)(&haystack[i]));
		--i;
	}
	return (NULL);
}
