/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   auto_other_possibility.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihwang <ihwang@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/27 13:59:10 by marvin            #+#    #+#             */
/*   Updated: 2020/10/01 00:27:35 by ihwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "auto_completion.h"
size_t		measure_len_filling_up(t_auto *auto_com)
{
	size_t	ret;
	size_t	target_len;
	t_list	*p_list;

	ret = auto_com->largest_list_size;
	target_len = ft_strlen(auto_com->target_str);
	p_list = auto_com->list;
	while (p_list)
	{
		if (ft_strnequ((char*)p_list->content, auto_com->target_str, target_len))
		{
			if (ret > p_list->content_size)
				ret = p_list->content_size;
		}
		p_list = p_list->next;
	}
	return (ret);
}

char		is_partialy_completed(t_auto *auto_com, size_t *len)
{
	*len = measure_len_filling_up(auto_com);
	return (ft_strlen(auto_com->target_str) == *len);
}

char		*get_largest_str(t_auto *auto_com)
{
	char	*ret;
	t_list	*iter;

	iter = auto_com->list;
	ret = NULL;
	while (iter)
	{
		if (iter->content_size == auto_com->largest_list_size)
		{
			ret = (char*)iter->content;
			break ;
		}
		iter = iter->next;
	}
	return (ret);
}

void		auto_fulfill_upto(size_t len, t_l *l)
{
	char	*target_for_printing;
	char	*largest_str;

	largest_str = get_largest_str(l->auto_com);
	target_for_printing = ft_strsub(largest_str, \
			(int)ft_strlen(l->auto_com->target_str), len);
    paste(l, NULL, 0, target_for_printing);
	delete_status_new_pos(&l->auto_com->status);
	ft_strdel(&target_for_printing);
}

void		auto_other_possibility(t_l *l)
{
	size_t	print_char_len;

	if (is_partialy_completed(l->auto_com, &print_char_len))
		//print
		NULL;
	else if (l->auto_com->target_str[0] != '\0')
		auto_fulfill_upto(print_char_len, l);
}
