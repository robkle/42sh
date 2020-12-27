/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_line.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthan <dthan@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/29 19:13:18 by ihwang            #+#    #+#             */
/*   Updated: 2020/12/27 16:49:14 by dthan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static int			parse_key(char t[], t_l *l)
{
	int				ret;

	ret = 0;
	if (t[0] == 127 && t[1] == '\0')
		ret = bs_key(l);
	else if (t[0] == '\v' && t[1] == '\0')
		ret = cutting(l, 0);
	else if (t[0] == '\f' && t[1] == '\0')
		ret = paste(l, NULL, 0, NULL);
	else if (t[0] == 27 && t[1] == 91 && t[2] == 'H')
		ret = home_key(l);
	else if (t[0] == 27 && t[1] == 91 && t[2] == 'F')
		ret = end_key(l);
	else if (t[0] == '\t')
		ret = auto_complete(l);
	if (ret != AUTO_COMPLETION)
		set_status_new_pos(&l->auto_com.status);
	return (ret);
}

static void			parse_key_arrow(char t[], t_l *l)
{
	if ((t[0] == 27 && t[1] == 91 && t[2] == 'A')
		|| (t[0] == 27 && t[1] == 91 && t[2] == 'B'))
		up_down(l, t);
	else if (t[0] == 27 && t[1] == 91 && t[2] == 'D')
		left_key(l);
	else if (t[0] == 27 && t[1] == 91 && t[2] == 'C')
		right_key(l);
	else if (!ft_strcmp(t, "\x1b[1;5A"))
		ctrl_up(l);
	else if (!ft_strcmp(t, "\x1b[1;5B"))
		ctrl_down(l);
	else if (!ft_strcmp(t, "\x1b[1;5C"))
		ctrl_right(l);
	else if (!ft_strcmp(t, "\x1b[1;5D"))
		ctrl_left(l, 0);
	else if (ft_strlen(t) > 1 && ft_isprint(t[0]))
		paste(l, t, 0, NULL);
	else if (ft_isprint(t[0]) || (t[0] == '\x04' && l->nb == 0))
		add_key(t, l);
	else if (t[0] == 18 && !t[1])
		ft_reverse_search(l);
	else if (t[0] == 27 && !t[1] && l->rs)
		ft_reverse_search_reset(l);
	set_status_new_pos(&l->auto_com.status);
}

void				ft_get_line(t_l *l)
{
	char			tmp[BUFF_LINE_EDITION];

//	int				debug = 0;

	init_term(l);
	while (1)
	{
		ft_bzero(tmp, sizeof(tmp));
		if (!(g_shell.signal_indicator == SIGINT))
	//	if (debug == 0)
			read(0, tmp, sizeof(tmp));
		if (g_shell.signal_indicator == SIGINT)
	//	if (debug == 1)
		{
			post_sigint(l);
			continue ;
		}
		else if (g_shell.signal_indicator == SIGWINCH)
		{
			post_sigwinch(l);
			continue ;
		}
		if (tmp[0] == '\n')
			return (carriage_return_key(l));
		if (!parse_key(tmp, l))
			parse_key_arrow(tmp, l);
		if (l->line && (l->line[0] == '\x04' && l->line[1] == '\0'))
			return (eof_handler(l));
	}
}
