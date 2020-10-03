/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   auto_open_path.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihwang <ihwang@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/27 13:47:23 by marvin            #+#    #+#             */
/*   Updated: 2020/10/02 18:43:10 by ihwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "auto_completion.h"

size_t			get_count(t_auto *auto_com)
{
	t_list		*iter;
	size_t		count;
	char		*content;
	char		*target_str;

	iter = auto_com->list;
	count = 0;
	target_str = auto_com->target_str;
	while (iter != NULL)
    {
		content = iter->content;
		if ((!ft_strequ(content, "./") && !ft_strequ(content, "../")) || \
				((ft_strequ(content, "./") ||ft_strequ(content, "../")) && \
				(ft_strequ(target_str, ".") || ft_strequ(target_str, ".."))))
        	count++;
        iter = iter->next;
    }
	return (count);
}

char            get_list_and_count(t_auto *auto_com)
{
    int         count;
    DIR     	*dirp;

	dirp = opendir(auto_com->full_path);
    auto_get_list(auto_com, dirp);
    closedir(dirp);
    count = get_count(auto_com);
	if (count > 0)
       set_status_word_in_path(&auto_com->status);
    return (count);
}

void		auto_open_path(t_l *l)
{
	size_t	count;

	count = get_list_and_count(&l->auto_com);
	if (count == 0)
		return ;
	else if (count > 1)
	{
		set_status_other_possibility(&l->auto_com.status);
		auto_other_possibility(l);
	}
    else
		auto_no_other_possibility(l);
}

