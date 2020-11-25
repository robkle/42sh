/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   auto_print_list.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihwang <ihwang@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/28 13:50:11 by marvin            #+#    #+#             */
/*   Updated: 2020/11/25 17:51:07 by ihwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "auto_completion.h"

void auto_read_input(char first, char second, char buf[])
{
	while ((read(STDIN_FILENO, buf, sizeof(BUFF_LINE_EDITION))) > 1 ||
		   (buf[0] != first && buf[0] != second))
	{
		if (g_shell.signal_indicator & SIGINT_INDICATOR)
		//if (1)
		{
			g_shell.signal_indicator &= ~SIGINT_INDICATOR;
			break;
		}
		if (buf[0] == 'q')
			break;
		ft_beep_sound();
		ft_bzero(buf, sizeof(BUFF_LINE_EDITION));
	}
}

size_t get_longest_col_len(t_list *list)
{
	size_t ret;

	ret = 0;
	while (list)
	{
		if (list->content_size > ret)
			ret = list->content_size;
		list = list->next;
	}
	return (ret + 5);
}

size_t get_file_count(t_list *list)
{
	size_t ret;

	ret = 0;
	while (list)
	{
		if (list->content)
			++ret;
		list = list->next;
	}
	return (ret);
}

void get_grid_vars(t_l *l, t_auto_grid *grd)
{
	grd->longest_col_len = get_longest_col_len(l->auto_com.list);
	grd->file_count = get_file_count(l->auto_com.list);
	grd->col_count = (size_t)(l->co / grd->longest_col_len);
	if (grd->col_count == 0)
		grd->col_count += 1;
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

void print_each(
	size_t *row, size_t *col, t_auto_grid *grid, t_list *p_list)
{
	if ((*row == grid->end_row && *col < grid->filled_col_count) ||
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

void restore_line_edition(t_l *l)
{
	auto_reset(&l->auto_com);
	ft_putchar('\n');
	get_prompt();
	ft_putstr(l->line);
	apply_termcap_str("cm", l->x, l->y + get_current_row() - 1);
	l->starting_row = l->total_row - get_current_row() - 1;
	ft_beep_sound();
}

void print_in_term_size(t_l *l, t_auto_grid *grid)
{
	size_t col;
	size_t row;
	t_list *p_list;

	p_list = l->auto_com.list;
	row = grid->start_row;
	col = 0;
	while (p_list)
	{
		print_each(&row, &col, grid, p_list);
		p_list = p_list->next;
	}
	apply_termcap_str("cm", 0, grid->end_row);
	restore_line_edition(l);
}

t_list *get_midnode(t_auto *auto_com, size_t midindex)
{
	t_list *p_list;
	size_t idx;

	p_list = auto_com->list;
	idx = 0;
	while (idx != midindex)
	{
		p_list = p_list->next;
		idx++;
	}
	return (p_list);
}

void wait_for_space_or_carrage_return(char *buf)
{
	ft_putstr("--More--");
	auto_read_input('\n', ' ', buf);
}

void fill_screen_with_single_column(t_list **list, int total_row)
{
	size_t line_count;

	line_count = 0;
	while (line_count < (size_t)total_row && *list)
	{
		ft_printf("%s\n", (char *)(*list)->content);
		*list = (*list)->next;
		line_count++;
	}
}

void fill_one_line(t_list **head)
{
	ft_printf("%s\n", (char *)(*head)->content);
	*head = (*head)->next;
}

void print_in_one_column(t_l *l)
{
	t_list *head;
	char buf[BUFF_LINE_EDITION];

	head = l->auto_com.list;
	ft_putchar('\n');
	fill_screen_with_single_column(&head, l->total_row - 1);
	wait_for_space_or_carrage_return(buf);
	while (head)
	{
		apply_termcap_str("cm", 0, get_current_row() - 1);
		apply_termcap_str("cd", 0, 0);
		if (buf[0] == '\n')
			fill_one_line(&head);
		else if (buf[0] == ' ')
			fill_screen_with_single_column(&head, l->total_row - 1);
		else
			return;
		if (head)
			wait_for_space_or_carrage_return(buf);
	}
	apply_termcap_str("cm", 0, l->total_row - 1);
	apply_termcap_str("cd", 0, 0);
}

void fill_screen_with_two_columns(
	t_list **head, t_list **midnode, t_l *l)
{
	size_t line_count;
	size_t total_row;
	size_t col_size;

	line_count = 0;
	total_row = (size_t)(l->total_row - 1);
	col_size = l->auto_com.largest_content_size + 4;
	while (line_count < total_row && *head && *midnode)
	{
		ft_printf("%*.*s", -col_size, col_size, (char *)(*head)->content);
		ft_printf("%s\n", (char *)(*midnode)->content);
		*head = (*head)->next;
		*midnode = (*midnode)->next;
		line_count++;
	}
}

void fill_one_line2(t_list **head, t_list **midnode, t_l *l)
{
	size_t col_size;

	col_size = l->auto_com.largest_content_size + 4;
	ft_printf("%*.*s", -col_size, col_size, (char *)(*head)->content);
	ft_printf("%s\n", (char *)(*midnode)->content);
	*head = (*head)->next;
	*midnode = (*midnode)->next;
}

void print_in_two_columns(t_l *l)
{
	t_list *head;
	t_list *midnode;
	char buf[BUFF_LINE_EDITION];

	midnode = get_midnode(&l->auto_com, (size_t)(l->auto_com.count_list / 2));
	head = l->auto_com.list;
	ft_putchar('\n');
	fill_screen_with_two_columns(&head, &midnode, l);
	wait_for_space_or_carrage_return(buf);
	while (head && midnode)
	{
		apply_termcap_str("cm", 0, get_current_row() - 1);
		//apply_termcap_str("cd", 0, 0);
		if (buf[0] == '\n')
			fill_one_line2(&head, &midnode, l);
		else if (buf[0] == ' ')
			fill_screen_with_two_columns(&head, &midnode, l);
		else
			return;
		if (midnode)
			wait_for_space_or_carrage_return(buf);
		else
			ft_printf("%s\n", (char *)head->content);
	}
	apply_termcap_str("cm", 0, l->total_row - 1);
	apply_termcap_str("cd", 0, 0);
}

void print_over_term_size(t_l *l)
{
	char *count;
	char buf[BUFF_LINE_EDITION];

	count = ft_itoa(l->auto_com.count_list);
	ft_printf("Display all %s possibilities? (y or n)", count);
	ft_strdel(&count);
	ft_bzero(buf, sizeof(BUFF_LINE_EDITION));
	auto_read_input('y', 'n', buf);
	if (buf[0] == 'y')
	{
		if (l->auto_com.largest_content_size + 10 > (size_t)l->co)
			print_in_one_column(l);
		else
			print_in_two_columns(l);
	}
	else
	{
		//		read(STDIN_FILENO, buf, 1);
		ft_putchar('\n');
	}
	restore_line_edition(l);
}

void auto_print_list(t_l *l)
{
	t_auto_grid grid;

	apply_termcap_str("do", 0, 0);
	get_grid_vars(l, &grid);
	if ((size_t)(grid.file_count / grid.col_count) > (size_t)l->total_row)
		print_over_term_size(l);
	else
		print_in_term_size(l, &grid);
}
