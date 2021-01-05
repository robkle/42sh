/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   auto_completion.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthan <dthan@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/21 17:13:51 by marvin            #+#    #+#             */
/*   Updated: 2021/01/05 19:33:53 by dthan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

char			auto_is_separator(char c)
{
    return (c == '&' || c == ';' || c == '|');
}

int				auto_is_command(t_l *l)
{
	int			head;
	int			curr;

	curr = l->x + (l->y * l->co) - l->pmpt - 1;
	head = curr;
	if (head < 0)
		return (TRUE);
	while (head > 0 && ft_isalnum(l->line[head]) && \
			!auto_is_separator(l->line[head]) && !ft_isspace(l->line[head]))
		--head;
	while (head > 0 && ft_isspace(l->line[head]))
		--head;
	if ((head == 0 || auto_is_separator(l->line[head])) && \
		l->line[head] != '.' && l->line[head] != '/')	
		return (TRUE);
	else
		return (FALSE);
}

void        auto_reset(t_auto *auto_com)
{
	auto_lstdel_strdel(&auto_com->list);
    ft_strdel(&auto_com->target_str);
    ft_strdel(&auto_com->typed_str);
	ft_memset(auto_com->cwd, 0, PATH_MAX);
	ft_memset(auto_com->full_path, 0, PATH_MAX);
	auto_com->count_list = 0;
	auto_com->largest_content_size = 0;
	auto_com->status = 0;
}

void init_auto_completion_struct(t_auto *auto_com)
{
	ft_bzero(auto_com, sizeof(t_auto));
	auto_com->list = NULL;
	auto_com->count_list = 0;
	auto_com->largest_content_size = 0;
	auto_com->largest_content = NULL;
	// auto_com->cwd
	// auto_com->full_path
	auto_com->typed_str = NULL;
	auto_com->target_str = NULL;
	auto_com->path_env = NULL;
	auto_com->status = 0;
}

// old
int         auto_complete(t_l *l)
{
	static char sticky;
	int		stat;

    if ((stat = auto_is_command(l)) == TRUE)
		auto_command(l);
    else if (stat == AUTO_COMPLETION)
		return (AUTO_COMPLETION);
	else
        auto_file(l);
    delete_status_new_pos(&l->auto_com.status);
    return (AUTO_COMPLETION);
}

// new
int         auto_complete(t_l *l)
{
	t_auto auto_com;
	int		stat;

	init_auto_completion_struct(&auto_com);
    if ((stat = auto_is_command(l)) == TRUE)
		auto_command(l);
    else if (stat == AUTO_COMPLETION)
		return (AUTO_COMPLETION);
	else
        auto_file(l);
    delete_status_new_pos(&l->auto_com.status);
    return (AUTO_COMPLETION);
}
