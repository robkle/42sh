/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   auto_print_list.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihwang <ihwang@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/28 13:50:11 by marvin            #+#    #+#             */
/*   Updated: 2020/10/15 16:32:29 by ihwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "auto_completion.h"

size_t				get_longest_col_len(t_list *list)
{
	size_t			ret;

	ret = 0;
	while (list)
	{
		if (list->content_size > ret)
			ret = list->content_size;
		list = list->next;
	}
	return (ret + 5);
}

size_t				get_file_count(t_list *list)
{
	size_t			ret;

	ret = 0;
	while (list)
	{
		if (list->content)
			++ret;
		list = list->next;
	}
	return (ret);
}

void				get_grid_vars(t_l *l, t_auto_grid *grd)
{
	grd->longest_col_len = get_longest_col_len(l->auto_com.list);
	grd->file_count = get_file_count(l->auto_com.list);
	grd->col_count = l->co / grd->longest_col_len;
	grd->start_row = get_current_row() - 1;
	if (grd->file_count % grd->col_count)
	{
		grd->end_row = grd->file_count / grd->col_count + grd->start_row + 1;
		grd->filled_col_count = grd->file_count % grd->col_count;
	}
	else
	{
		grd->end_row = grd->file_count / grd->col_count + grd->start_row;
		grd->filled_col_count = grd->col_count;
	}
    if (grd->end_row > (size_t)l->total_row - 1)
    {
		grd->start_row = grd->start_row - (grd->end_row - (l->total_row - 1));
        grd->end_row = grd->end_row - (grd->end_row - (l->total_row - 1));
    }
}

void				print_each( \
size_t *row, size_t *col, t_auto_grid *grid, t_list *p_list)
{
	if ((*row == grid->end_row && *col < grid->filled_col_count) || \
		(*row == grid->end_row - 1 && *col >= grid->filled_col_count))
	{
		*row = grid->start_row;
		++(*col);
	}
	if (*col != 0)
		apply_termcap_str("cm", *col * grid->longest_col_len, *row);
	ft_putstr(p_list->content);
	++(*row);
	if (*col == 0)
		apply_termcap_str("do", 0, 0);
}

void				print_in_term_size(t_l *l, t_auto_grid *grid)
{
	size_t			col;
	size_t			row;
	t_list			*p_list;

	p_list = l->auto_com.list;
	row = grid->start_row;
	col = 0;
	while (p_list)
	{
		print_each(&row, &col, grid, p_list);
		p_list = p_list->next;
	}
	apply_termcap_str("cm", 0, grid->end_row);
 	auto_reset(&l->auto_com);
	get_prompt();
	ft_putstr(l->line);
	l->starting_row = get_current_row() - 1;
	apply_termcap_str("cm", l->x, l->y + l->starting_row);
	ft_beep_sound();
}

t_list				*get_midpoint(t_auto *auto_com, size_t midindex)
{
	t_list			*p_list;
	size_t			idx;

	p_list = auto_com->list;
	idx = 0;
	while (idx != midindex)
	{
		p_list = p_list->next;
		idx++;
	}
	return (p_list);
}

void				wait_for_space_or_carrage_return(char buf[])
{
	ft_putstr("--More--");
	ft_bzero(buf, sizeof(buf));
	while ((read(STDIN_FILENO, buf, sizeof(buf))) > 1 || \
			(buf[0] != '\n' && buf[0] != ' '))
	{
		ft_beep_sound();
		ft_bzero(buf, sizeof(buf));
	}
}

void				fill_screen_with_single_column(\
t_list **list, size_t total_row, size_t *line_count)
{
	while (line_count < total_row - 1)
	{
		ft_putstr((char*)(*list)->content);
		ft_putchar('\n');
		*list = (*list)->next;
		line_count++;
	}
}

void				print_line_by_line(t_l *l, t_auto_grid *grid)
{
	size_t			line_count;
	t_list			*head;
	t_list			*midpoint;
	char			buf[8];

	grid = NULL;
	line_count = 0;
	ft_putchar('\n');
	head = l->auto_com.list;
	if (l->auto_com.largest_content_size + 10 > (size_t)l->co)
	{
		ft_putchar('\n');
		while (head)
		{
			fill_screen_with_single_column(\
				&head, (size_t)l->total_row, &line_count);
			wait_for_space_or_carrage_return(buf);
			if (buf[0] == '\n')
			{
				ft_put
			}
			else if (buf[0] == ' ')
			{
				NULL;
			}
		}
	}
	else
	{
		midpoint = get_midpoint(&l->auto_com, l->auto_com.count_list / 2);
	}
}

void				print_over_term_size(t_l *l, t_auto_grid *grid)
{
	char			*count;
	char			buf[8];

	grid = 0;
	count = ft_itoa(l->auto_com.count_list);
	ft_bzero(buf, sizeof(buf));
	ft_putstr("Display all ");
	ft_putstr(count);
	ft_strdel(&count);
	ft_putstr(" possibilities? (y or n)");
	while ((read(STDIN_FILENO, buf, sizeof(buf))) > 1 || \
		(buf[0] != 'y' && buf[0] != 'n'))
	{
		ft_beep_sound();
		ft_bzero(buf, sizeof(buf));
	}
	if (buf[0] == 'y')
		print_line_by_line(l, grid);
	else	
		return ;
}

void				auto_print_list(t_l *l)
{
	t_auto_grid		grid;

	apply_termcap_str("do", 0, 0);
	get_grid_vars(l, &grid);
	if (grid.file_count / grid.col_count > (size_t)l->total_row)
		print_over_term_size(l, &grid);
	else
		print_in_term_size(l, &grid);
}
