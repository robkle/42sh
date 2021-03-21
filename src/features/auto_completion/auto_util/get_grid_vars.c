/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_grid_var.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihwang <ihwang@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/21 14:09:58 by ihwang            #+#    #+#             */
/*   Updated: 2021/03/21 14:10:51 by ihwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static size_t	get_longest_col_len(t_list *list)
{
	size_t ret;

	ret = 0;
	while (list)
	{
		if (list->content_size > ret)
			ret = list->content_size;
		list = list->next;
	}
	return (ret + 5);
}

static size_t	get_file_count(t_list *list)
{
	size_t ret;

	ret = 0;
	while (list)
	{
		if (list->content)
			++ret;
		list = list->next;
	}
	return (ret);
}

void			get_grid_vars(t_auto *auto_com, t_auto_grid *grd)
{
	t_l		*edtr;

	edtr = auto_com->editor;
	grd->longest_col_len = get_longest_col_len(auto_com->list);
	grd->file_count = get_file_count(auto_com->list);
	grd->col_count = (size_t)(edtr->co / grd->longest_col_len);
	if (grd->col_count == 0)
		grd->col_count += 1;
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
	if (grd->end_row > (size_t)edtr->total_row - 1)
	{
		grd->start_row = \
		grd->start_row - (grd->end_row - (edtr->total_row - 1));
		grd->end_row = grd->end_row - (grd->end_row - (edtr->total_row - 1));
	}
}
