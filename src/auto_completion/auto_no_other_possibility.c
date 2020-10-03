/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   auto_no_other_possibility.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihwang <ihwang@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/27 13:47:17 by marvin            #+#    #+#             */
/*   Updated: 2020/10/02 18:50:37 by ihwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "auto_completion.h"
#include "add_key.h"

void		add_one_extra_char(t_l *l)
{
	char	buf_for_addkey[2];

	ft_memset(buf_for_addkey, 0, sizeof(buf_for_addkey));
	buf_for_addkey[0] = ' ';
	add_key(buf_for_addkey, l);
}
// vim resource/ 에서 tab누를때, 자꾸 ./가 나옴
void        fulfill(t_l *l)
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

void        auto_no_other_possibility(t_l *l)
{
	char	*completed_target;

	if (!(l->auto_com.status & AUTO_STAT_COMPLETED))
		fulfill(l);
	completed_target = get_completed_target_str(l);
	if (auto_is_dir(l->auto_com.full_path, completed_target))
		set_status_dir(&l->auto_com.status);
	else
		delete_status_dir(&l->auto_com.status);
	if (!(l->auto_com.status & AUTO_STAT_DIR))
		add_one_extra_char(l);
	else if (l->auto_com.status & AUTO_STAT_COMPLETED)
		auto_dir(l);
	set_status_completed(&l->auto_com.status);
	ft_bzero(l->auto_com.full_path, PATH_MAX);
	auto_lstdel_strdel(&l->auto_com.list);
	l->auto_com.count_list = 0;
	ft_strdel(&completed_target);
}
