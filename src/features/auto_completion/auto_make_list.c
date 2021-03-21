/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   auto_make_list.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihwang <ihwang@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/28 13:50:06 by marvin            #+#    #+#             */
/*   Updated: 2021/03/21 13:52:44 by ihwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static char		is_duplicated_cmd(t_list *list, char *cmd)
{
	while (list)
	{
		if (ft_strequ((char *)list->content, cmd))
			return (TRUE);
		list = list->next;
	}
	return (FALSE);
}

void			auto_make_list(char path[], t_auto *auto_com)
{
	t_list		*node;
	DIR			*dirp;
	t_dirent	*dir;
	size_t		target_str_len;

	dirp = opendir(path);
	target_str_len = ft_strlen(auto_com->target_str);
	while ((dir = readdir(dirp)))
	{
		if (ft_strnequ(auto_com->target_str, dir->d_name, target_str_len) &&
			!is_duplicated_cmd(auto_com->list, dir->d_name))
		{
			auto_com->count_list++;
			node = ft_lstnew_str((void *)dir->d_name, ft_strlen(dir->d_name));
			if (auto_com->list == NULL)
				auto_com->list = node;
			else
				auto_add_list_on_spot(auto_com, node);
		}
	}
	closedir(dirp);
}
