/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   auto_get_list.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihwang <ihwang@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/27 16:44:30 by marvin            #+#    #+#             */
/*   Updated: 2020/10/03 00:33:35 by ihwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "auto_completion.h"

void			create_list(t_auto *auto_com, char filename[])
{
    t_list      *node;

	node = ft_lstnew_str((void*)filename, ft_strlen(filename));
	if (node->content_size > auto_com->largest_list_size)
	{
		auto_com->largest_list_size = node->content_size;
		auto_com->largest_content = node->content;
	}
	if (auto_com->list == NULL)
		auto_com->list = node;
	else
		ft_lstadd_end(&auto_com->list, node);
}

void            auto_get_list(t_auto *auto_com, DIR *dirp)
{
    t_dirent    *dir;
    size_t      target_len;
	char		identical;

	char *debug;

	identical = FALSE;
	target_len = ft_strlen(auto_com->target_str);
    while ((dir = readdir(dirp)))
    {
		debug = dir->d_name;
		if (ft_strnequ(dir->d_name, auto_com->target_str, target_len) || \
			auto_com->status & AUTO_STAT_DIR)
		{
			if (ft_strequ(dir->d_name, auto_com->target_str))
				identical = TRUE;
			if (auto_is_dir(auto_com->full_path, dir->d_name))
                ft_strcat(dir->d_name, "/");
			create_list(auto_com, dir->d_name);
			++auto_com->count_list;
		}
    }
	if (identical == FALSE)
		delete_status_completed(&auto_com->status);
}

//				!auto_is_dir(auto_com->full_path, auto_com->target_str))