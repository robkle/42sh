/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ctrl_k.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthan <dthan@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/20 00:18:39 by ihwang            #+#    #+#             */
/*   Updated: 2021/03/15 15:54:00 by rklein           ###   ########.fr       */
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

static void	apply_to_screen(t_l *l, int i/*, int j, int y_dec*/)
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
	/*if (l->x < l->x + (l->y * l->co) - l->pmpt - i)//OLD
	{
		l->y -= y_dec;
		while (y_dec--)
			apply_termcap_str("up", 0, 0);
	}
	apply_termcap_str("ch", 0, (i + l->pmpt) % l->co);
	l->x = (i + l->pmpt) % l->co;
	apply_termcap_str("cd", 0, 0);
	apply_termcap_str("sc", 0, 0);
	ft_putstr(&l->line[i]);
	apply_termcap_str("rc", 0, 0);
	l->nb -= (j - i);*/
}

static void	clip_edit_apply(t_l *l, int i, int j/*, int y_dec*/)
{
	
	cutting_clipping(l, i, j);
	edit_line(l, i, j);
	apply_to_screen(l, i/*, j*/);
}
	
int			cutting(t_l *l/*, int y_dec*/)
{
	int				curr;
	int				i;
	int				j;

	//i = l->x + (l->y * l->co) - l->pmpt;//OLD
	i = ft_index_calc(l);//NEW
	curr = i;
	while (i >= 0)
	{
		if (ft_strlen(l->line) == 0)
			return (EXIT_SUCCESS);
		//OLD
		//if ((ft_iswhite(l->line[i ? i - 1 : 0]) && !ft_iswhite(l->line[i]) &&
		//!ft_iswhite(l->line[curr])) || (i == 0 && !ft_iswhite(l->line[curr])))
		//NEW
		if ((ft_isspace(l->line[i ? i - 1 : 0]) && !ft_isspace(l->line[i]) && \
		!ft_isspace(l->line[curr])) || (i == 0 && !ft_isspace(l->line[curr])))
		{
			j = i - 1;
			while (++j < l->nb)
				//if (ft_iswhite(l->line[j]))//OLD
				if (ft_isspace(l->line[j]))//NEW
					break ;
			clip_edit_apply(l, i, j/*, y_dec*/);
			break ;
		}
		//(i + l->pmpt) % l->co == 0 ? y_dec++ : 0;//OLD
		i--;
	}
	return (EXIT_SUCCESS);
}
