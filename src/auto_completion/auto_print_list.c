/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   auto_print_list.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihwang <ihwang@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/28 13:50:11 by marvin            #+#    #+#             */
/*   Updated: 2020/10/05 01:29:52 by ihwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "auto_completion.h"

size_t				get_longest_col_len(t_list *list)
{
	size_t			ret;

	ret = 0;
	while (list)
	{
		if (list->content_size > ret)
			ret = list->content_size;
		list = list->next;
	}
	return (ret + 5);
}

size_t				get_file_count(t_list *list)
{
	size_t			ret;

	ret = 0;
	while (list)
	{
		if (list->content)
			++ret;
		list = list->next;
	}
	return (ret);
}

void				get_print_info(t_l *l, t_auto_print *print_info)
{
	size_t			longest_col_len;
	size_t			term_col_len;
	size_t			col_count;
	size_t			row_count;
	size_t			file_count;

	file_count = get_file_count(l->auto_com.list);
	longest_col_len = get_longest_col_len(l->auto_com.list);
	term_col_len = l->co;
	col_count = term_col_len / longest_col_len;
	if (file_count % col_count)
		row_count = file_count / col_count + 1;
	else
		row_count = file_count / col_count;
	print_info->file_count = file_count;
	print_info->longest_col_len = longest_col_len;
	print_info->term_col_len = term_col_len;
	print_info->col_count = col_count;
	print_info->row_count = row_count;
}

void				auto_print_list(t_l *l)
{
	t_auto_print	info;
	size_t			col_len;
	size_t			starting_row;
	size_t			row;
	t_list			*p_list;

	get_print_info(l, &info);
	p_list = l->auto_com.list;
	col_len = 0;
	ft_putchar('\n');
	starting_row = get_current_row() - 1;
	info.row_count += starting_row;
	while (col_len < info.term_col_len && p_list)
	{
		row = starting_row;
		while (row < info.row_count && p_list)
		{
			apply_termcap_str("cm", col_len, row);
			ft_putstr(p_list->content);
			p_list = p_list->next;
			++row;
		}
		col_len += info.longest_col_len;
	}
	auto_reset(&l->auto_com);
	apply_termcap_str("cm", 0, info.row_count);
	size_t prompt_len = get_prompt();
	size_t prompt_row_count;
	if (l->co % prompt_len)
		prompt_row_count = l->co / prompt_len + 1;
	else
		prompt_row_count = l->co / prompt_len;
	ft_putstr(l->line);
	l->starting_row = l->starting_row - (row - starting_row) - prompt_row_count - 1;
	//apply_termcap_str("cm", l->x, l->total_row - l->starting_row - l->y);
}
