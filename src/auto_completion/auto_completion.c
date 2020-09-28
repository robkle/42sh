/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   auto_completion.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihwang <ihwang@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/21 17:13:51 by marvin            #+#    #+#             */
/*   Updated: 2020/09/28 14:29:41 by ihwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "auto_completion.h"

int         is_separator(char c)
{
    return (c == '&' || c == ';' || c == '|');
}

int         auto_is_command(t_l *l)
{
    int     curr;

    curr = l->x + (l->y * l->co) - l->pmpt - 1;
    while (curr != 0 && !ft_iswhite(l->line[curr]) && \
        !is_separator(l->line[curr]))
        --curr;    
    if (curr == 0)
        return (1);
    else if (ft_iswhite(l->line[curr]))
    {
        while (curr != 0 && ft_iswhite(l->line[curr]))
            --curr;
        if (curr == 0)
            return (1);
        else
            return (0);
    }
    return (0);
}

// void        auto_command(t_l *l)
// {

// }


// void        auto_no_completed(t_l *l)
// {
//     if (auto_is_dir(l))
//         auto_dir(l);
//     else
//         return ;
// }


// void        auto_typed_upto(t_l *l)
// {
//     if (auto_is_ready_print(l))
//         auto_print_list(l);
//     else
//         auto_make_list(l);
// }

void        reset_auto(t_l *l)
{
	ft_lstdel_strdel(&l->auto_com->list);
	l->auto_com->count_list = 0;
    ft_strdel(&l->auto_com->path);
    ft_strdel(&l->auto_com->word);
    //free(l->auto_com);
}

int         auto_complete(t_l *l)
{
    if (l->auto_com->status & AUTO_STAT_NEW_POS)
        reset_auto(l);
    if (auto_is_command(l))
        NULL;
   //     auto_command(l);
    else
        auto_file(l);
    delete_status_new_pos(&l->auto_com->status);
    return (AUTO_COMPLETION);
}
