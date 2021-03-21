/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   auto_lstdel_strdel.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihwang <ihwang@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/01 23:26:06 by marvin            #+#    #+#             */
/*   Updated: 2021/03/21 03:58:37 by ihwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void		auto_lstdel_strdel(t_list **alst)
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
		free(temp_lst);
	}
	*alst = NULL;
}
