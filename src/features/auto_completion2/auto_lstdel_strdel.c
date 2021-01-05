/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   auto_lstdel_strdel.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthan <dthan@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/01 23:26:06 by marvin            #+#    #+#             */
/*   Updated: 2020/12/27 17:49:39 by dthan            ###   ########.fr       */
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

