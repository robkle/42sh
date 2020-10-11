/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   auto_print_list.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihwang <ihwang@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/28 13:50:11 by marvin            #+#    #+#             */
/*   Updated: 2020/10/11 10:04:23 by ihwang           ###   ########.fr       */
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

void				get_coords_vars(t_l *l, t_auto_print *grd)
{
	grd->longest_col_len = get_longest_col_len(l->auto_com.list);
	grd->file_count = get_file_count(l->auto_com.list);
	grd->col_count = l->co / grd->longest_col_len;
	grd->start_row = get_current_row() - 1;
	if (grd->file_count % grd->col_count)
	{
		grd->end_row = grd->file_count / grd->col_count + grd->start_row + 1;
		grd->filled_col_count = grd->file_count % grd->col_count;
	}
	else
	{
		grd->end_row = grd->file_count / grd->col_count + grd->start_row;
		grd->filled_col_count = grd->col_count;
	}
    if (grd->end_row > (size_t)l->total_row - 1)
    {
		grd->start_row = grd->start_row - (grd->end_row - (l->total_row - 1));
        grd->end_row = grd->end_row - (grd->end_row - (l->total_row - 1));
    }
}

void				auto_print_list(t_l *l)
{
	t_auto_print	coords;
	size_t			col;
	size_t			row;
	t_list			*p_list;

	apply_termcap_str("do", 0, 0);
	get_coords_vars(l, &coords);
	p_list = l->auto_com.list;
	row = coords.start_row;
	col = 0;
	while (p_list)
	{
		if ((row == coords.end_row && col < coords.filled_col_count) || \
			(row == coords.end_row - 1 && col >= coords.filled_col_count))
		{
			row = coords.start_row;
			++col;
		}
		if (col != 0)
			apply_termcap_str("cm", col * coords.longest_col_len, row);
		ft_putstr(p_list->content);
		++row;
		if (col == 0)
			apply_termcap_str("do", 0, 0);
		p_list = p_list->next;
	}
	apply_termcap_str("cm", 0, coords.end_row);
 	auto_reset(&l->auto_com);
	get_prompt();
	ft_putstr(l->line);
	l->starting_row = get_current_row() - 1;
}
