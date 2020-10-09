/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   up_down_key.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihwang <ihwang@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/20 00:21:14 by ihwang            #+#    #+#             */
/*   Updated: 2020/08/06 02:03:24 by ihwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static void			up_down_key_apply_statuses(t_l *l)
{
	int				i;
	int				line_rows;
	int				starting_row_from_top;
	int				new_starting_row;

	l->nb = ft_strlen(l->line);
	line_rows = (l->nb + l->pmpt) / l->co;
	new_starting_row = l->starting_row;
	if (l->starting_row < line_rows)
		new_starting_row = line_rows;
	starting_row_from_top = l->total_row - l->starting_row;
	i = get_current_row() - starting_row_from_top;
	while (i-- > 0)
		apply_termcap_str("up", 0, 0);
	apply_termcap_str("ch", 0, l->pmpt);
	apply_termcap_str("cd", 0, 0);
	l->y = (l->nb + l->pmpt) / l->co;
	l->x = (l->nb + l->pmpt) % l->co;
	l->starting_row = new_starting_row;
	ft_putstr(l->line);
	if (l->x == 0)
		ft_putchar('\n');
}

static void			up_key(t_l *l)
{
	int				i;

	if (g_h->curr == 0 || g_h->hst == 0 || g_h->hst == g_h->curr - HISTSIZE) 
		return ;
	g_h->hst--;
	i = g_h->curr >= HISTSIZE ? g_h->curr - (g_h->hst % HISTSIZE) : \
		g_h->curr - (g_h->hst % g_h->curr);
	ft_strdel(&l->line);
	l->line = ft_strdup(g_h->hist[i]);
	up_down_key_apply_statuses(l);
}

static void			down_key(t_l *l, char *first)
{
	int				i;

	if (g_h->curr == 0 || g_h->hst == g_h->curr)
		return ;
	g_h->hst++;
	i = g_h->curr >= HISTSIZE ? g_h->curr - (g_h->hst % HISTSIZE) : \
		g_h->curr - (g_h->hst % g_h->curr);
	if (i != g_h->curr)
		l->line = ft_strdup(g_h->hist[i]);
	else
		l->line = first ? ft_strdup(first) : ft_strnew(0);	
	up_down_key_apply_statuses(l);
}

void				up_down(t_l *l, char t[])
{
	static char		*tmp;

	if (t == NULL)
		ft_strdel(&tmp);
	else if (t[0] == 27 && t[1] == 91 && t[2] == 'A')
	{
		if (g_h->hst == g_h->curr && l->line && ft_isprint(l->line[0]))
			tmp = ft_strdup(l->line);
		up_key(l);
	}
	else if (t[0] == 27 && t[1] == 91 && t[2] == 'B')
		down_key(l, tmp);
}
