/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_key.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthan <dthan@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/20 00:11:40 by ihwang            #+#    #+#             */
/*   Updated: 2021/03/19 22:51:40 by rklein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static void	append_char(char t[], t_l *l)
{
	char	*tmp;

	if (l->line == NULL)
		l->line = ft_strnew(2);
	tmp = ft_strjoin(l->line, t);
	ft_strdel(&l->line);
	l->line = tmp;
	if (t[0] != '\n')
		ft_putstr(&l->line[l->nb]);
	if (l->x != l->co - 1)
		l->x++;
	else
	{
		l->x = 0;
		l->y++;
		if (get_current_row() == (size_t)l->total_row)
		{
			ft_putchar('\n');
			l->starting_row++;
		}
		apply_termcap_str("cm", 0, get_current_row());
	}
	l->nb++;
}

static void	store_cursor_position(t_l *l)
{
	if (l->x != l->co - 1)
		l->x++;
	else
	{
		l->x = 0;
		l->y++;
	}
	l->nb++;
}

static void	insert_char(char t[], t_l *l)
{
	char		*tmp;
	int			insert;
	int			add_row[2];

	insert = ft_index_calc(l);
	add_row[0] = ft_row_count(l);
	tmp = ft_strnew(l->nb + 1);
	tmp = ft_strncpy(tmp, l->line, insert);
	tmp = ft_addchar(tmp, t[0]);
	tmp = ft_strcat(tmp, &l->line[insert]);
	ft_strdel(&l->line);
	l->line = tmp;
	ft_putchar(t[0]);
	if (l->x != l->co - 1)
		apply_termcap_str("cd", 0, 0);
	else
		apply_termcap_str("do", 0, 0);
	apply_termcap_str("sc", 0, 0);
	ft_putstr(&l->line[insert + 1]);
	apply_termcap_str("rc", 0, 0);
	add_row[1] = ft_row_count(l);
	l->starting_row += add_row[1] - add_row[0];
	store_cursor_position(l);
}

int			add_key(char t[], t_l *l)
{
	if (l->rs)
		ft_reverse_search_add(t, l);
	else
	{
		if (l->nb != ft_index_calc(l))
			insert_char(t, l);
		else
			append_char(t, l);
	}
	return (EXIT_SUCCESS);
}
