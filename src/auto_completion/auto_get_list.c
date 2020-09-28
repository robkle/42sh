/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   auto_get_list.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihwang <ihwang@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/27 16:44:30 by marvin            #+#    #+#             */
/*   Updated: 2020/09/29 00:06:46 by ihwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "auto_completion.h"

// void            auto_get_list(t_auto *auto_com, DIR *dirp)
// {
//     t_dirent    *dir;
//     size_t      word_len;
//     t_list      *node;

//     word_len = ft_strlen(auto_com->word);
//     while ((dir = readdir(dirp)))
//     {
//         if (ft_strnequ(dir->d_name, auto_com->word, word_len))
//         {
//             if (auto_is_dir(auto_com->path, dir->d_name))
//                 ft_strcat(dir->d_name, "/");
//             node = ft_lstnew((void*)ft_strdup(dir->d_name), ft_strlen(dir->d_name));
//             if (auto_com->list == NULL)
//                 auto_com->list = node;
//             else
//                 ft_lstadd_end(&auto_com->list, node);
// 			++auto_com->count_list;
//         }
//     }
// }

void            auto_get_list(t_auto *auto_com, DIR *dirp)
{
    t_dirent    *dir;
    size_t      word_len;
    t_list      *node;

    word_len = ft_strlen(auto_com->word);
    while ((dir = readdir(dirp)))
    {
		if (ft_strnequ(dir->d_name, auto_com->word, word_len) ||
			auto_com->status & AUTO_STAT_DIR)
		{
			if (auto_is_dir(auto_com->path, dir->d_name))
                ft_strcat(dir->d_name, "/");
            node = ft_lstnew((void*)ft_strdup(dir->d_name), ft_strlen(dir->d_name));
            if (auto_com->list == NULL)
                auto_com->list = node;
            else
                ft_lstadd_end(&auto_com->list, node);
			++auto_com->count_list;
		}
    }
}