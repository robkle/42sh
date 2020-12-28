/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   auto_make_list.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthan <dthan@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/28 13:50:06 by marvin            #+#    #+#             */
/*   Updated: 2020/12/27 17:49:44 by dthan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void		del_lst(t_auto *auto_com)
{
	t_list	*temp_list;
	char	*temp_content;

	while (auto_com->list)
	{
		temp_list = auto_com->list;
		temp_content = (char*)temp_list->content;
		ft_strdel(&temp_content);
		auto_com->list = auto_com->list->next;
		free(temp_list);
	}
	auto_com->list = NULL;
}

void			auto_make_list(t_auto *auto_com)
{
	DIR			*dirp;

	if (auto_com->list && !(auto_com->status & AUTO_STAT_LIST))
		del_lst(auto_com);
	dirp = opendir(auto_com->full_path);
	auto_get_list(auto_com, dirp);
	closedir(dirp);
}

