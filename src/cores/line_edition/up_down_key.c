/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   up_down_key.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihwang <ihwang@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/20 00:21:14 by ihwang            #+#    #+#             */
/*   Updated: 2021/03/19 21:57:11 by rklein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static void	up_down_key_apply_statuses(t_l *l)
{
	int				i;
	int				row_nb;
	int				starting_row_from_top;
	int				new_starting_row;

	row_nb = ft_row_count(l) - 1;
	l->y = row_nb;
	l->x = ft_cursor_x(l);
	l->nb = ft_strlen(l->line);
	new_starting_row = l->starting_row;
	if (l->starting_row < row_nb)
		new_starting_row = row_nb;
	starting_row_from_top = l->total_row - l->starting_row;
	i = get_current_row() - starting_row_from_top;
	while (i-- > 0)
		apply_termcap_str("up", 0, 0);
	apply_termcap_str("ch", 0, l->pmpt);
	apply_termcap_str("cd", 0, 0);
	l->starting_row = new_starting_row;
	ft_putstr(l->line);
	if (l->x == 0)
		ft_putchar('\n');
}

int			up_key(t_l *l)
{
	int len;
	int	d;

	if (g_shell.history->curr == 0 || g_shell.history->hst == 0)
		return (EXIT_SUCCESS);
	g_shell.history->hst--;
	ft_strdel(&l->line);
	len = ft_strlen(g_shell.history->hist[g_shell.history->hst]);
	d = g_shell.history->hist[g_shell.history->hst][len - 1] == 4 ? 2 : 1;
	l->line = ft_strndup(g_shell.history->hist[g_shell.history->hst], \
	len - d);
	up_down_key_apply_statuses(l);
	return (EXIT_SUCCESS);
}

static void	down_key(t_l *l)
{
	int len;
	int	d;

	if (g_shell.history->curr == 0 ||
		g_shell.history->hst == g_shell.history->curr)
		return ;
	g_shell.history->hst++;
	ft_strdel(&l->line);
	if (g_shell.history->hst != g_shell.history->curr)
	{
		len = ft_strlen(g_shell.history->hist[g_shell.history->hst]);
		d = g_shell.history->hist[g_shell.history->hst][len - 1] == 4 ? 2 : 1;
		l->line = ft_strndup(g_shell.history->hist[g_shell.history->hst], \
		len - d);
	}
	else
	{
		l->line = l->current ? ft_strdup(l->current) : ft_strnew(0);
		ft_strdel(&l->current);
		l->current = NULL;
	}
	up_down_key_apply_statuses(l);
}

int			up_down(t_l *l, char t[])
{
	if (l->rs)
		ft_reverse_search_reset(l);
	else if (ft_strequ(t, UP_ARROW_KEY))
	{
		if (g_shell.history->hst == g_shell.history->curr && l->line &&
			ft_isprint(l->line[0]))
			l->current = ft_strdup(l->line);
		up_key(l);
	}
	else if (ft_strequ(t, DOWN_ARROW_KEY))
		down_key(l);
	return (EXIT_SUCCESS);
}
