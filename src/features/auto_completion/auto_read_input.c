/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   auto_read_input.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihwang <ihwang@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/21 14:00:31 by ihwang            #+#    #+#             */
/*   Updated: 2021/03/21 14:00:43 by ihwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void		auto_read_input(const char *input_set, char buf[])
{
	while ((read(STDIN_FILENO, buf, sizeof(BUFF_LINE_EDITION))) > 1 ||
			(!ft_strchr(input_set, buf[0])))
	{
		if (g_shell.signal_indicator == SIGINT)
			break ;
		ft_beep_sound();
		ft_bzero(buf, sizeof(BUFF_LINE_EDITION));
	}
}
