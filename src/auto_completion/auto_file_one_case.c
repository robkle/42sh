/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   auto_file_one_case.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihwang <ihwang@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/27 13:47:17 by marvin            #+#    #+#             */
/*   Updated: 2020/10/16 22:53:19 by ihwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "auto_completion.h"

void        auto_complete_cmd_file(t_l *l)
{
    char    *p_fulfill;

    p_fulfill = l->auto_com.list->content + \
				ft_strlen(l->auto_com.target_str);
    paste(l, NULL, 0, p_fulfill);
}

char		*get_completed_target_str(t_l *l)
{
	ft_strdel(&l->auto_com.typed_str);
    l->auto_com.typed_str = auto_get_typed_str(l);
	return (auto_get_target_str(&l->auto_com));
}

void        auto_file_one_case(t_l *l)
{
	char	*completed_target;

	if (!(l->auto_com.status & AUTO_STAT_COMPLETED))
		auto_complete_cmd_file(l);
	completed_target = get_completed_target_str(l);
	if (auto_is_dir(l->auto_com.full_path, completed_target))
		set_status_dir(&l->auto_com.status);
	else
		delete_status_dir(&l->auto_com.status);
	if (!(l->auto_com.status & AUTO_STAT_DIR))
		auto_add_one_extra_char(l, ' ');
	else if (l->auto_com.status & AUTO_STAT_COMPLETED)
		auto_dir(l);
	set_status_completed(&l->auto_com.status);
	ft_bzero(l->auto_com.full_path, PATH_MAX);
	auto_lstdel_strdel(&l->auto_com.list);
	l->auto_com.count_list = 0;
	ft_strdel(&completed_target);
}
