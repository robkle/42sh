/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   auto_print_list.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihwang <ihwang@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/28 13:50:11 by marvin            #+#    #+#             */
/*   Updated: 2021/03/21 14:15:20 by ihwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int				auto_print_list(t_auto *auto_com)
{
	t_auto_grid grid;

	apply_termcap_str("do", 0, 0);
	get_grid_vars(auto_com, &grid);
	if ((size_t)(grid.file_count / grid.col_count) \
	> (size_t)auto_com->editor->total_row)
		return (auto_print_over_term_size(auto_com));
	else
		return (auto_print_in_term_size(auto_com, &grid));
}
