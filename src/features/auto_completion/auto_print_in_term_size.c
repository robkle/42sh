/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   auto_print_in_term_size.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihwang <ihwang@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/21 14:05:59 by ihwang            #+#    #+#             */
/*   Updated: 2021/03/21 14:08:40 by ihwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static void	print_each(
	size_t *row, size_t *col, t_auto_grid *grid, t_list *p_list)
{
	if ((*row == grid->end_row && *col < grid->filled_col_count) ||
		(*row == grid->end_row - 1 && *col >= grid->filled_col_count))
	{
		*row = grid->start_row;
		++(*col);
	}
	if (*col != 0)
		apply_termcap_str("cm", *col * grid->longest_col_len, *row);
	ft_putstr(p_list->content);
	++(*row);
	if (*col == 0)
		apply_termcap_str("do", 0, 0);
}

int			auto_print_in_term_size(t_auto *auto_com, t_auto_grid *grid)
{
	size_t	col;
	size_t	row;
	t_list	*p_list;

	p_list = auto_com->list;
	row = grid->start_row;
	col = 0;
	while (p_list)
	{
		print_each(&row, &col, grid, p_list);
		p_list = p_list->next;
	}
	apply_termcap_str("cm", 0, grid->end_row);
	restore_line_edition(auto_com);
	return (clear_auto_struct(auto_com));
}
