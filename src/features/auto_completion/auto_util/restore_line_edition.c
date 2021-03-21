/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   restore_line_edition.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihwang <ihwang@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/21 14:07:01 by ihwang            #+#    #+#             */
/*   Updated: 2021/03/21 14:07:27 by ihwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void		restore_line_edition(t_auto *auto_com)
{
	t_l		*editor;

	editor = auto_com->editor;
	if (g_shell.signal_indicator != SIGINT)
	{
		print_info();
		print_prompt(auto_com->editor->promp_type);
	}
	ft_putstr(editor->line);
	apply_termcap_str("cm", editor->x, editor->y + get_current_row() - 1);
	editor->starting_row = editor->total_row - get_current_row() - 1;
	ft_beep_sound();
}
