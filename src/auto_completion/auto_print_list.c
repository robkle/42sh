/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   auto_print_list.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihwang <ihwang@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/28 13:50:11 by marvin            #+#    #+#             */
/*   Updated: 2020/09/28 13:50:50 by ihwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "auto_completion.h"

void        auto_print_list(t_l *l)
{
    t_list  *trav;

    trav = l->auto_com->list;
    while (trav)
    {
        ft_putstr((char*)l->auto_com->list->content);
        ft_putchar('\n');
        trav = trav->next;
    }
}
