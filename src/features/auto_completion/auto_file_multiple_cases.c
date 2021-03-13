/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   auto_file_multiple_cases.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihwang <ihwang@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/27 13:59:10 by marvin            #+#    #+#             */
/*   Updated: 2021/03/13 21:18:11 by ihwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

size_t		get_common_length(char *str1, char *str2)
{
	int		ret;

	ret = 0;
	while (*str1 && *str2)
	{
		if (*str1 == *str2)
			++ret;
		else
			break ;
		++str1;
		++str2;
	}
	return (ret);
}

size_t		measure_len_filling_up(t_auto *auto_com)
{
	size_t	ret;
	size_t	target_len;
	size_t	common_len;
	t_list	*p_list;
	char	*largest_str;

	ret = auto_com->largest_content_size;
	target_len = ft_strlen(auto_com->target_str);
	p_list = auto_com->list;
	largest_str = (char*)auto_com->largest_content;
	while (p_list)
	{
		if (ft_strnequ((char*)p_list->content, auto_com->target_str, target_len))
		{
			common_len = get_common_length(largest_str, (char*)p_list->content);
			if (ret > common_len)
				ret = common_len;
		}
		p_list = p_list->next;
	}
	ret = ret - target_len;
	return (ret);
}

char		is_partially_completed(t_auto *auto_com, size_t *printable_char_len)
{
	*printable_char_len = measure_len_filling_up(auto_com);
	return (!(*printable_char_len > 0));
}

int		auto_complete_upto(size_t len, t_auto *auto_com)
{
	char	*target_for_printing;
	char	*largest_str;

	largest_str = (char*)auto_com->largest_content;
	target_for_printing = ft_strsub(largest_str, \
			(int)ft_strlen(auto_com->target_str), len);
    paste(auto_com->editor, NULL, target_for_printing);
	delete_status_new_pos(&auto_com->status);
	ft_strdel(&target_for_printing);
	return (clear_auto_struct(auto_com));
}

int		auto_cmd_file_multiple_cases(t_auto *auto_com)
{
	size_t	print_char_len;

	if (is_partially_completed(auto_com, &print_char_len))
		return (auto_print_list(auto_com));
	else if (auto_com->target_str[0] != '\0')
		return (auto_complete_upto(print_char_len, auto_com));
	return (clear_auto_struct(auto_com));
}
