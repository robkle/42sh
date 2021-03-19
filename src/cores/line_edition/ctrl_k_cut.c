/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ctrl_k_cut.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthan <dthan@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/20 00:18:39 by ihwang            #+#    #+#             */
/*   Updated: 2021/03/19 22:55:58 by rklein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static void	edit_line(t_l *l, int i, int j)
{
	char			*tmp;

	tmp = ft_strnew(l->nb - (j - i));
	tmp = ft_strncpy(tmp, l->line, i);
	tmp = ft_strcat(tmp, &l->line[j]);
	ft_strdel(&l->line);
	l->line = tmp;
}

static void	apply_to_screen(t_l *l, int i)
{
	int x;
	int	line_rows;
	int	starting_row_from_top;
	int	new_starting_row;

	line_rows = ft_row_count(l);
	l->y = line_rows - 1;
	l->x = ft_cursor_x(l);
	l->nb = ft_strlen(l->line);
	new_starting_row = l->starting_row;
	if (l->starting_row < line_rows)
		new_starting_row = line_rows;
	starting_row_from_top = l->total_row - l->starting_row;
	x = get_current_row() - starting_row_from_top;
	while (x-- > 0)
		apply_termcap_str("up", 0, 0);
	apply_termcap_str("ch", 0, 0);
	apply_termcap_str("cd", 0, 0);
	l->starting_row = new_starting_row;
	print_prompt(l->promp_type);
	ft_putstr(l->line);
	home_key(l);
	x = 0;
	while (++x <= i)
		right_key(l);
}

static void	clip_edit_apply(t_l *l, int i, int j)
{
	cutting_clipping(l, i, j);
	edit_line(l, i, j);
	apply_to_screen(l, i);
}

int			cutting(t_l *l)
{
	int				curr;
	int				i;
	int				j;

	i = ft_index_calc(l);
	curr = i;
	while (i >= 0)
	{
		if (ft_strlen(l->line) == 0)
			return (EXIT_SUCCESS);
		if ((ft_isspace(l->line[i ? i - 1 : 0]) && !ft_isspace(l->line[i]) && \
		!ft_isspace(l->line[curr])) || (i == 0 && !ft_isspace(l->line[curr])))
		{
			j = i - 1;
			while (++j < l->nb)
				if (ft_isspace(l->line[j]))
					break ;
			clip_edit_apply(l, i, j);
			break ;
		}
		i--;
	}
	return (EXIT_SUCCESS);
}
