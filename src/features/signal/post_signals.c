/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   post_signals.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthan <dthan@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/31 15:39:59 by marvin            #+#    #+#             */
/*   Updated: 2021/01/05 16:22:08 by dthan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

/*
char		*dquote_post_sigint(t_l *l)
{
	ft_strdel(&l->line);
	g_shell.signal_indicator = 0;
	g_shell.history->hst = g_shell.history->curr;
	up_down(l, NULL);
	ft_putchar('\n');
	return (NULL);
}

void		default_post_sigint(t_l *l)
{
	int tmp_pmpt;
	int current_row;

	tmp_pmpt = l->pmpt;
	current_row = get_current_row();
	apply_termcap_str("cm", l->x, current_row - 1);
	apply_termcap_str("cd", 0, 0);
	ft_strdel(&l->line);
	ft_memset(l, 0, sizeof(*l));
	l->total_row = tgetnum("li");
	l->starting_row = l->total_row - current_row;
	l->pmpt = tmp_pmpt;
	l->x = l->pmpt;
	l->co = tgetnum("co");
	ft_putchar('\n');
	get_prompt();
	g_shell.signal_indicator = 0;
	g_shell.history->hst = g_shell.history->curr;//NEW
	up_down(l, NULL); //NEW
}
*/
/*
void		post_sigwinch(t_l *l)
{
	int		len_pmpt;

	apply_termcap_str("cl", 0, 0);
	len_pmpt = get_prompt() - l->pmpt;
	l->co = tgetnum("co");
	l->total_row = tgetnum("li");
	l->starting_row = l->total_row - get_current_row();
	l->x = l->pmpt;
	l->y = 0;
	if (l->line)
		ft_putstr(l->line);
	apply_termcap_str("cm", l->pmpt, len_pmpt / l->co + 1);
	g_shell.signal_indicator = 0;
}
*/