/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_line.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihwang <ihwang@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/29 19:13:18 by ihwang            #+#    #+#             */
/*   Updated: 2020/09/27 11:12:35 by ihwang           ###   ########.fr       */
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
		ret = ctrl_k(l, 0);
	else if (t[0] == '\f' && t[1] == '\0')
		ret = paste(l, NULL, 0, NULL);
	else if (t[0] == 27 && t[1] == 91 && t[2] == 'H')
		ret = home_key(l);
	else if (t[0] == 27 && t[1] == 91 && t[2] == 'F')
		ret = end_key(l);
	else if (t[0] == '\t')
		ret = auto_complete(l);
	if (ret != AUTO_COMPLETION)
		set_status_new_pos(&l->auto_com->status);
	return (ret);
}

static void			parse_key_arrow(char t[], t_l *l, t_h **h)
{
	if ((t[0] == 27 && t[1] == 91 && t[2] == 'A')
		|| (t[0] == 27 && t[1] == 91 && t[2] == 'B'))
		up_down(l, h, t);
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
	set_status_new_pos(&l->auto_com->status);
}

void				ft_get_line(t_l *l, t_h **h)
{
char			tmp[BUFF_LINE_EDITION];

	init_term(l);
	while (1)
	{
		ft_bzero(tmp, sizeof(tmp));
		if (!g_prompt)
			read(0, tmp, sizeof(tmp));
		if (g_prompt)
		{
			post_signal(l);
			continue ;
		}
		if (tmp[0] == '\n')
			return (carriage_return_key(l, h));
		if (!parse_key(tmp, l))
			parse_key_arrow(tmp, l, h);
		if (l->line && (l->line[0] == '\x04' && l->line[1] == '\0'))
			return (eof_handler(l));
	}
}
