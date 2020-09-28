/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   auto_ready_to_print.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihwang <ihwang@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/27 13:47:28 by marvin            #+#    #+#             */
/*   Updated: 2020/09/28 13:51:18 by ihwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "auto_completion.h"

char        is_ready_to_print(t_auto *auto_com)
{
    if (auto_com->list && auto_com->status & AUTO_STAT_LIST)
        return (TRUE);
    else
        return (FALSE);
}

void        auto_ready_to_print(t_l *l)
{
    if (is_ready_to_print(l->auto_com))
        auto_print_list(l);
	else
		auto_make_list(l->auto_com);
}
