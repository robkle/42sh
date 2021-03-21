/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   auto_open_path.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihwang <ihwang@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/27 13:47:23 by marvin            #+#    #+#             */
/*   Updated: 2021/03/21 14:16:18 by ihwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static size_t	get_count(t_auto *auto_com)
{
	t_list		*iter;
	size_t		count;
	char		*content;
	char		*target_str;

	iter = auto_com->list;
	count = 0;
	target_str = auto_com->target_str;
	while (iter != NULL)
	{
		content = iter->content;
		if ((!ft_strequ(content, "./") && !ft_strequ(content, "../")) || \
				((ft_strequ(content, "./") || ft_strequ(content, "../")) && \
				(ft_strequ(target_str, ".") || ft_strequ(target_str, ".."))))
			count++;
		iter = iter->next;
	}
	return (count);
}

static char		get_list_and_count(t_auto *auto_com)
{
	size_t		count;
	DIR			*dirp;
	char		list_status;

	dirp = opendir(auto_com->full_path);
	list_status = auto_get_list(auto_com, dirp);
	closedir(dirp);
	if (list_status == EXIT_FAILURE)
		return (-1);
	count = get_count(auto_com);
	auto_prune_list(auto_com, count);
	return (count);
}

int				auto_file_open_path(t_auto *auto_com)
{
	size_t	count;

	count = get_list_and_count(auto_com);
	if (count <= 0)
	{
		ft_beep_sound();
		return (clear_auto_struct(auto_com));
	}
	else if (count > 1)
		return (auto_cmd_file_multiple_cases(auto_com));
	else
		return (auto_file_one_case(auto_com));
}
