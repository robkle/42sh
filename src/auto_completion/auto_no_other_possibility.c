/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   auto_no_other_possibility.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihwang <ihwang@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/27 13:47:17 by marvin            #+#    #+#             */
/*   Updated: 2020/10/01 01:21:25 by ihwang           ###   ########.fr       */
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

    p_fulfill = l->auto_com->list->content + ft_strlen(l->auto_com->target_str);
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


void		lstdel_strdel(t_list **alst)
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

void        auto_no_other_possibility(t_l *l)
{
	char	*completed_target;

    if (!is_completed(l->auto_com))
        auto_fulfill(l);
	completed_target = auto_get_typed_str(l);
	if (auto_is_dir(l->auto_com->full_path, completed_target))
		set_status_dir(&l->auto_com->status);
	else
		delete_status_dir(&l->auto_com->status);
	if (l->auto_com->status & AUTO_STAT_DIR && \
		l->auto_com->status & AUTO_STAT_COMPLETED)	
		auto_dir(l);
	set_status_completed(&l->auto_com->status);
	ft_bzero(l->auto_com->full_path, PATH_MAX);
	lstdel_strdel(&l->auto_com->list);
	l->auto_com->count_list = 0;
	ft_strdel(&completed_target);
}
