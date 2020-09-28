/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdel_strdel.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihwang <ihwang@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/28 14:23:17 by marvin            #+#    #+#             */
/*   Updated: 2020/09/28 14:32:39 by ihwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		ft_lstdel_strdel(t_list **alst)
{
	t_list	*p_lst;
	t_list	*temp_lst;
	char	*copy_str;

	p_lst = *alst;
	while (p_lst)
	{
		copy_str = (char*)p_lst->content;
		ft_strdel(&copy_str);
		temp_lst = p_lst;
		p_lst = p_lst->next;
		free(temp_lst->content);
		free(temp_lst);
	}
	*alst = NULL;
}