/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   auto_print_over_term_size.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihwang <ihwang@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/21 13:58:29 by ihwang            #+#    #+#             */
/*   Updated: 2021/03/21 14:13:48 by ihwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int				auto_print_over_term_size(t_auto *auto_com)
{
	char		*count;
	char		buf[BUFF_LINE_EDITION];

	set_status_over_term_size(&auto_com->status);
	count = ft_itoa(auto_com->count_list);
	ft_printf("Display all %s possibilities? (y or n)", count);
	ft_strdel(&count);
	ft_bzero(buf, sizeof(BUFF_LINE_EDITION));
	auto_read_input("yn", buf);
	if (buf[0] == 'y')
	{
		if (auto_com->longest_len + 10 > (size_t)auto_com->editor->co)
			auto_print_in_one_column(auto_com);
		else
			auto_print_in_two_columns(auto_com);
	}
	else
		ft_putchar('\n');
	restore_line_edition(auto_com);
	delete_status_over_term_size(&auto_com->status);
	return (clear_auto_struct(auto_com));
}
