/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   post_sigwinch.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihwang <ihwang@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/16 01:11:00 by ihwang            #+#    #+#             */
/*   Updated: 2021/03/16 23:12:28 by ihwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void		handle_sigwinch(t_l *l)
{
	apply_termcap_str("cl", 0, 0);
	print_prompt(l->promp_type);
	l->co = tgetnum("co");
	l->total_row = tgetnum("li");
	l->y = ft_row_count(l) - 1;
	l->x = ft_cursor_x(l);
	l->nb = ft_strlen(l->line);
	l->starting_row = l->total_row - get_current_row();
	if (l->line)
		ft_putstr(l->line);
	g_shell.signal_indicator = 0;
}