/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_end.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihwang <ihwang@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/27 14:46:48 by ihwang            #+#    #+#             */
/*   Updated: 2020/09/25 21:49:56 by ihwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

void			ft_lstadd_end(t_list **alst, t_list *new)
{
	t_list		*p_list;

	if (*alst == NULL)
		return ;
	p_list = *alst;
	while (p_list->next != NULL)
		p_list = p_list->next;
	p_list->next = new;
}
