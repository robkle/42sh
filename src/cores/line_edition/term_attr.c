/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   term_attr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthan <dthan@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/20 00:14:04 by ihwang            #+#    #+#             */
/*   Updated: 2021/01/28 14:09:03 by dthan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	restore_term(t_l *l)
{
	end_key(l);
	apply_termcap_str("do", 0, 0);
	tcsetattr(0, TCSANOW, &g_shell.shell_tmode);
}

t_term	get_set_default_term(t_term *t)
{
	static t_term	old;

	if (t)
		old = *t;
	return (old);
}

/*
** init term - changed to cooked mode
**	We turn off canonical mode + echo mode + ctrl-c and ctrl-z signal
**	We set the VMIN and VTIME which are timeout for read()
**		VMIN = the minimum value of bytes of input neede before read()
**		VTIME = the maximum value of time to wait before read() return
*/

void	init_term(void)
{
	t_term	raw;

	tcgetattr(0, &raw);
	raw.c_lflag &= ~(ICANON | ECHO);
	raw.c_cc[VMIN] = 1;
	raw.c_cc[VTIME] = 0;
	tcsetattr(0, TCSANOW, &raw);
}
