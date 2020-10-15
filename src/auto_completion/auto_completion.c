/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   auto_completion.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihwang <ihwang@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/21 17:13:51 by marvin            #+#    #+#             */
/*   Updated: 2020/10/14 22:44:25 by ihwang           ###   ########.fr       */
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
    while (curr > 0 && !ft_iswhite(l->line[curr]) && \
        !is_separator(l->line[curr]))
        --curr;    
    if (curr == 0 || curr == -1)
        return (TRUE);
    else if (ft_iswhite(l->line[curr]))
    {
        while (curr != 0 && ft_iswhite(l->line[curr]))
            --curr;
        if (curr == 0)
            return (TRUE);
        else
            return (FALSE);
    }
    return (FALSE);
}

void        auto_reset(t_auto *auto_com)
{
	auto_lstdel_strdel(&auto_com->list);
    ft_strdel(&auto_com->target_str);
    ft_strdel(&auto_com->typed_str);
	ft_memset(auto_com->cwd, 0, PATH_MAX);
	ft_memset(auto_com->full_path, 0, PATH_MAX);
	auto_com->count_list = 0;
	auto_com->largest_content_size = 0;
	auto_com->status = 0;
}

int         auto_complete(t_l *l)
{
	if (l->auto_com.status & AUTO_STAT_NEW_POS)
        auto_reset(&l->auto_com);
	delete_status_new_pos(&l->auto_com.status);
	if (l->line == NULL)
		l->line = ft_strnew(0);
    if (auto_is_command(l))
		auto_command(l);
    else
        auto_file(l);
    delete_status_new_pos(&l->auto_com.status);
    return (AUTO_COMPLETION);
}
