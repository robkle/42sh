/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   auto_print_in_one_column.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihwang <ihwang@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/21 14:11:55 by ihwang            #+#    #+#             */
/*   Updated: 2021/03/21 15:05:36 by ihwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static void	fill_one_line(t_list **head)
{
	ft_printf("%s\n", (char *)(*head)->content);
	*head = (*head)->next;
}

void		fill_column(t_list **list, int total_row)
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

static char	fill_screen(t_list **head, char buf[], t_l *editor)
{
	if (buf[0] == '\n')
		fill_one_line(head);
	else if (buf[0] == ' ')
		fill_column(head, editor->total_row - 1);
	else if (buf[0] == 'q')
	{
		ft_putchar('\n');
		return (FALSE);
	}
	else if (g_shell.signal_indicator == SIGINT)
		return (FALSE);
	if (*head)
		wait_for_space_or_carrage_return(buf);
	return (TRUE);
}

int			auto_print_in_one_column(t_auto *auto_com)
{
	t_list	*head;
	char	buf[BUFF_LINE_EDITION];
	t_l		*editor;

	editor = auto_com->editor;
	head = auto_com->list;
	ft_putchar('\n');
	fill_column(&head, editor->total_row - 1);
	wait_for_space_or_carrage_return(buf);
	while (head)
	{
		apply_termcap_str("cm", 0, get_current_row() - 1);
		apply_termcap_str("cd", 0, 0);
		if (fill_screen(&head, buf, editor) == FALSE)
			return (clear_auto_struct(auto_com));
	}
	apply_termcap_str("cm", 0, editor->total_row - 1);
	apply_termcap_str("cd", 0, 0);
	return (clear_auto_struct(auto_com));
}
