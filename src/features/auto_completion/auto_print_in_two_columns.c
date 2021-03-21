/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   auto_print_in_two_columns.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihwang <ihwang@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/21 14:13:35 by ihwang            #+#    #+#             */
/*   Updated: 2021/03/21 15:01:09 by ihwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static t_list	*get_midnode(t_auto *auto_com, size_t midindex)
{
	t_list		*p_list;
	size_t		idx;

	p_list = auto_com->list;
	idx = 0;
	while (idx != midindex)
	{
		p_list = p_list->next;
		idx++;
	}
	return (p_list);
}

static void		fill_one_line(t_list **head, t_list **midnode, t_auto *auto_com)
{
	size_t col_size;

	col_size = auto_com->longest_len + 4;
	ft_printf("%*.*s", -col_size, col_size, (char *)(*head)->content);
	ft_printf("%s\n", (char *)(*midnode)->content);
	*head = (*head)->next;
	*midnode = (*midnode)->next;
}

static void		fill_two_columns(
	t_list **head, t_list **midnode, t_auto *auto_com)
{
	size_t line_count;
	size_t total_row;
	size_t col_size;

	line_count = 0;
	total_row = (size_t)(auto_com->editor->total_row - 1);
	col_size = auto_com->longest_len + 4;
	while (line_count < total_row && *head && *midnode)
	{
		ft_printf("%*.*s", -col_size, col_size, (char *)(*head)->content);
		ft_printf("%s\n", (char *)(*midnode)->content);
		*head = (*head)->next;
		*midnode = (*midnode)->next;
		line_count++;
	}
}

static char		fill_screen(
	t_list **head, t_list **midnode, t_auto *auto_com, char buf[])
{
	if (buf[0] == '\n')
		fill_one_line(head, midnode, auto_com);
	else if (buf[0] == ' ')
		fill_two_columns(head, midnode, auto_com);
	else if (buf[0] == 'q')
	{
		ft_putchar('\n');
		return (FALSE);
	}
	else if (g_shell.signal_indicator == SIGINT)
		return (FALSE);
	if (*midnode)
		wait_for_space_or_carrage_return(buf);
	else
		ft_printf("%s\n", (char *)(*head)->content);
	return (TRUE);
}

int				auto_print_in_two_columns(t_auto *auto_com)
{
	t_list		*head;
	t_list		*midnode;
	char		buf[BUFF_LINE_EDITION];

	midnode = get_midnode(auto_com, (size_t)(auto_com->count_list / 2));
	head = auto_com->list;
	ft_putchar('\n');
	fill_two_columns(&head, &midnode, auto_com);
	wait_for_space_or_carrage_return(buf);
	while (head && midnode)
	{
		apply_termcap_str("cm", 0, get_current_row() - 1);
		if (fill_screen(&head, &midnode, auto_com, buf) == FALSE)
			return (clear_auto_struct(auto_com));
	}
	apply_termcap_str("cm", 0, auto_com->editor->total_row - 1);
	apply_termcap_str("cd", 0, 0);
	return (clear_auto_struct(auto_com));
}
