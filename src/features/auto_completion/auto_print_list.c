/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   auto_print_list.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthan <dthan@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/28 13:50:11 by marvin            #+#    #+#             */
/*   Updated: 2021/01/07 19:04:03 by dthan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void auto_read_input(const char *input_set, char buf[])
{
	while ((read(STDIN_FILENO, buf, sizeof(BUFF_LINE_EDITION))) > 1 ||
		   (!ft_strchr(input_set, buf[0])))
	{
		if (g_shell.signal_indicator == SIGINT)
		//if (1)
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

void get_grid_vars(t_auto *auto_com, t_auto_grid *grd)
{
	t_l *edtr;

	edtr = auto_com->editor;
	grd->longest_col_len = get_longest_col_len(auto_com->list);
	grd->file_count = get_file_count(auto_com->list);
	grd->col_count = (size_t)(edtr->co / grd->longest_col_len);
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
	if (grd->end_row > (size_t)edtr->total_row - 1)
	{
		grd->start_row = grd->start_row - (grd->end_row - (edtr->total_row - 1));
		grd->end_row = grd->end_row - (grd->end_row - (edtr->total_row - 1));
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

void restore_line_edition(t_auto *auto_com)
{
	t_l *editor;

	editor = auto_com->editor;
	if (g_shell.signal_indicator != SIGINT)
	{
		print_info();
		print_prompt(auto_com->editor->promp_type);
	}
	ft_putstr(editor->line);
	apply_termcap_str("cm", editor->x, editor->y + get_current_row() - 1);
	editor->starting_row = editor->total_row - get_current_row() - 1;
	ft_beep_sound();
}

int		auto_print_in_term_size(t_auto *auto_com, t_auto_grid *grid)
{
	size_t col;
	size_t row;
	t_list *p_list;

	p_list = auto_com->list;
	row = grid->start_row;
	col = 0;
	while (p_list)
	{
		print_each(&row, &col, grid, p_list);
		p_list = p_list->next;
	}
	apply_termcap_str("cm", 0, grid->end_row);
	restore_line_edition(auto_com);
	return (clear_auto_struct(auto_com));
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
	auto_read_input("\n q", buf);
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

int		auto_print_in_one_column(t_auto *auto_com)
{
	t_list *head;
	char buf[BUFF_LINE_EDITION];
	t_l *editor;

	editor = auto_com->editor;
	head = auto_com->list;
	ft_putchar('\n');
	fill_screen_with_single_column(&head, editor->total_row - 1);
	wait_for_space_or_carrage_return(buf);
	while (head)
	{
		apply_termcap_str("cm", 0, get_current_row() - 1);
		apply_termcap_str("cd", 0, 0);
		if (buf[0] == '\n')
			fill_one_line(&head);
		else if (buf[0] == ' ')
			fill_screen_with_single_column(&head, editor->total_row - 1);
		else if (buf[0] == 'q')
		{
			ft_putchar('\n');
			return (clear_auto_struct(auto_com));
		}
		else if (g_shell.signal_indicator == SIGINT)
			return (clear_auto_struct(auto_com));
		if (head)
			wait_for_space_or_carrage_return(buf);
	}
	apply_termcap_str("cm", 0, editor->total_row - 1);
	apply_termcap_str("cd", 0, 0);
	return (clear_auto_struct(auto_com));
}

void fill_screen_with_two_columns(
	t_list **head, t_list **midnode, t_auto *auto_com)
{
	size_t line_count;
	size_t total_row;
	size_t col_size;

	line_count = 0;
	total_row = (size_t)(auto_com->editor->total_row - 1);
	col_size = auto_com->largest_content_size + 4;
	while (line_count < total_row && *head && *midnode)
	{
		ft_printf("%*.*s", -col_size, col_size, (char *)(*head)->content);
		ft_printf("%s\n", (char *)(*midnode)->content);
		*head = (*head)->next;
		*midnode = (*midnode)->next;
		line_count++;
	}
}

void fill_one_line2(t_list **head, t_list **midnode, t_auto *auto_com)
{
	size_t col_size;

	col_size = auto_com->largest_content_size + 4;
	ft_printf("%*.*s", -col_size, col_size, (char *)(*head)->content);
	ft_printf("%s\n", (char *)(*midnode)->content);
	*head = (*head)->next;
	*midnode = (*midnode)->next;
}

int		auto_print_in_two_columns(t_auto *auto_com)
{
	t_list *head;
	t_list *midnode;
	char buf[BUFF_LINE_EDITION];

	midnode = get_midnode(auto_com, (size_t)(auto_com->count_list / 2));
	head = auto_com->list;
	ft_putchar('\n');
	fill_screen_with_two_columns(&head, &midnode, auto_com);
	wait_for_space_or_carrage_return(buf);
	while (head && midnode)
	{
		apply_termcap_str("cm", 0, get_current_row() - 1);
		//apply_termcap_str("cd", 0, 0);
		if (buf[0] == '\n')
			fill_one_line2(&head, &midnode, auto_com);
		else if (buf[0] == ' ')
			fill_screen_with_two_columns(&head, &midnode, auto_com);
		else if (buf[0] == 'q')
		{
			ft_putchar('\n');
			return (clear_auto_struct(auto_com));
		}
		else if (g_shell.signal_indicator == SIGINT)
			return (clear_auto_struct(auto_com));
		if (midnode)
			wait_for_space_or_carrage_return(buf);
		else
			ft_printf("%s\n", (char *)head->content);
	}
	apply_termcap_str("cm", 0, auto_com->editor->total_row - 1);
	apply_termcap_str("cd", 0, 0);
	return (clear_auto_struct(auto_com));
}

int		auto_print_over_term_size(t_auto *auto_com)
{
	char *count;
	char buf[BUFF_LINE_EDITION];

	set_status_over_term_size(&auto_com->status);
	count = ft_itoa(auto_com->count_list);
	ft_printf("Display all %s possibilities? (y or n)", count);
	ft_strdel(&count);
	ft_bzero(buf, sizeof(BUFF_LINE_EDITION));
	auto_read_input("yn", buf);
	if (buf[0] == 'y')
	{
		if (auto_com->largest_content_size + 10 > (size_t)auto_com->editor->co)
			auto_print_in_one_column(auto_com);
		else
			auto_print_in_two_columns(auto_com);
	}
	else
		ft_putchar('\n');
	restore_line_edition(auto_com);
	delete_status_over_term_size(&auto_com->status);
	return (clear_auto_struct(auto_com));
}

int auto_print_list(t_auto *auto_com)
{
	t_auto_grid grid;

	apply_termcap_str("do", 0, 0);
	get_grid_vars(auto_com, &grid);
	if ((size_t)(grid.file_count / grid.col_count) > (size_t)auto_com->editor->total_row)
		return (auto_print_over_term_size(auto_com));
	else
		return (auto_print_in_term_size(auto_com, &grid));
}
