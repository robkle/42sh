/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   auto_no_other_possibility.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihwang <ihwang@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/27 13:47:17 by marvin            #+#    #+#             */
/*   Updated: 2020/09/29 00:04:14 by ihwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "auto_completion.h"

char        is_completed(t_auto *auto_com)
{
    //return (ft_strnequ(auto_com->word, (char*)auto_com->list->content, \
    //        ft_strlen(auto_com->word)));
    //return (ft_strnequ(auto_com->word, (char*)auto_com->list->content, \
    //        auto_com->list->content_size));
	return (auto_com->status & AUTO_STAT_COMPLETED);
}

void        auto_fulfill(t_l *l)
{
    char    *p_fulfill;

    p_fulfill = l->auto_com->list->content + ft_strlen(l->auto_com->word);
	delete_status_new_pos(&l->auto_com->status);
    paste(l, NULL, 0, p_fulfill);
}

// void        auto_no_other_possibility(t_l *l)
// {
// 	char	*completed_word;

//     if (is_completed(l->auto_com))
//     {
//         if (auto_is_dir(l->auto_com->path, l->auto_com->word))
//         {
//             set_status_dir(&l->auto_com->status);
//             auto_dir(l);
//         }
// 		else
// 		{
// 			delete_status_dir(&l->auto_com->status);
// 		}
//     }
//     else
// 	{
//         auto_fulfill(l);
// 		completed_word = auto_get_word(l);
// 		if (auto_is_dir(l->auto_com->path, completed_word))
// 			set_status_dir(&l->auto_com->status);
// 		ft_strdel(&completed_word);
//         set_status_completed(&l->auto_com->status);
// 	}
// }

void        auto_no_other_possibility(t_l *l)
{
	char	*completed_word;

    if (!is_completed(l->auto_com))
        auto_fulfill(l);
	set_status_completed(&l->auto_com->status);
	completed_word = auto_get_word(l);
	if (auto_is_dir(l->auto_com->path, completed_word))
	{
		set_status_dir(&l->auto_com->status);
		auto_dir(l);
	}
	else
		delete_status_dir(&l->auto_com->status);
	ft_strdel(&completed_word);
}
