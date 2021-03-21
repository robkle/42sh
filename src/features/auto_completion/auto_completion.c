/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   auto_completion.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihwang <ihwang@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/21 17:13:51 by marvin            #+#    #+#             */
/*   Updated: 2021/03/21 04:29:16 by ihwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

char		auto_is_separator(char c)
{
	return (c == '&' || c == ';' || c == '|');
}

int			auto_is_command(t_l *l)
{
	int head;
	int curr;

	curr = l->x + (l->y * l->co) - l->pmpt - 1;
	head = curr;
	if (head < 0)
		return (TRUE);
	while (head > 0 && ft_isalnum(l->line[head]) &&
	!auto_is_separator(l->line[head]) && !ft_isspace(l->line[head]))
		--head;
	while (head > 0 && ft_isspace(l->line[head]))
		--head;
	if ((head == 0 || auto_is_separator(l->line[head])) &&
		l->line[head] != '.' && l->line[head] != '/')
		return (TRUE);
	else
		return (FALSE);
}

void		init_auto_completion_struct(t_auto *auto_com, t_l *l)
{
	ft_bzero(auto_com, sizeof(t_auto));
	auto_com->editor = l;
}

int			clear_auto_struct(t_auto *auto_com)
{
	ft_lstdel_strdel(&auto_com->list);
	ft_strdel(&auto_com->target_str);
	ft_strdel(&auto_com->typed_str);
	if (g_shell.signal_indicator == SIGINT)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int			auto_complete(t_l *l)
{
	t_auto	auto_com;
	int		stat;

	ft_bzero(&auto_com, sizeof(t_auto));
	auto_com.editor = l;
	if ((stat = auto_is_command(l)) == TRUE)
		return (auto_command(&auto_com));
	return (auto_file(&auto_com));
}
