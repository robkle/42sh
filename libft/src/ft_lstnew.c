/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthan <dthan@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/27 14:47:20 by ihwang            #+#    #+#             */
/*   Updated: 2020/12/16 10:11:45 by dthan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"
#include <stdio.h>

t_list	*ft_lstnew(void const *content, size_t content_size)
{
	t_list *fresh;

	if (!(fresh = (t_list*)malloc(sizeof(t_list))))
		return (NULL);
	if (!content)
	{
		fresh->content = NULL;
		fresh->content_size = 0;
	}
	else
	{
		if (!(fresh->content = (void*)malloc(content_size)))
			return (NULL);
		ft_memcpy(fresh->content, content, content_size);
		fresh->content_size = content_size;
		printf("\n%s\n", (char*)fresh->content);
	}
	fresh->next = NULL;
	return (fresh);
}
