/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   up_down_key.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihwang <ihwang@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/20 00:21:14 by ihwang            #+#    #+#             */
/*   Updated: 2021/03/18 14:07:10 by rklein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int			ft_count_rows(t_l *l)
{
	int	count;
	int	row;
	int	i;
	int	lb;

	count = 0;
	row = 0;
	lb = 0;
	i = -1;
	while (l->line[++i])
	{
		if (l->line[i] == '\n')
		{
			row++;
			lb = 1;
			count = 0;
		}
		row = lb ? row + (count / l->co) : row + ((count + l->pmpt) / l->co);
		count++;
	}
	l->nb = count;
	l->y = row;
	l->x = lb ? count % l->co : (count + l->pmpt) % l->co;
	return (row);
}

static void	up_down_key_apply_statuses(t_l *l)
{
	int				i;
	int				row_nb;
	int				starting_row_from_top;
	int				new_starting_row;

	//line_rows = ft_count_rows(l);//OLD
	row_nb = ft_row_count(l) - 1;//NEW
	l->y = row_nb;//NEW
	l->x = ft_cursor_x(l);//NEW
	l->nb = ft_strlen(l->line);//NEW
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
	if (g_shell.history->curr == 0 || g_shell.history->hst == 0)
		return (EXIT_SUCCESS);
	g_shell.history->hst--;
	ft_strdel(&l->line);
	l->line = ft_strndup(g_shell.history->hist[g_shell.history->hst], \
	(int)ft_strlen(g_shell.history->hist[g_shell.history->hst]) - 1);//NEW
	//l->line = ft_strdup(g_shell.history->hist[g_shell.history->hst]);//OLD
	up_down_key_apply_statuses(l);
	return (EXIT_SUCCESS);
}

static void	down_key(t_l *l)
{
	if (g_shell.history->curr == 0 ||
		g_shell.history->hst == g_shell.history->curr)
		return ;
	g_shell.history->hst++;
	ft_strdel(&l->line);
	if (g_shell.history->hst != g_shell.history->curr)
	{
		l->line = ft_strndup(g_shell.history->hist[g_shell.history->hst], \
		(int)ft_strlen(g_shell.history->hist[g_shell.history->hst]) - 1);//NEW
		//l->line = ft_strdup(g_shell.history->hist[g_shell.history->hst]);//OLD
	}
	else
	{
		l->line = l->current ? ft_strdup(l->current) : ft_strnew(0);
		ft_strdel(&l->current);//
		l->current = NULL;//
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
