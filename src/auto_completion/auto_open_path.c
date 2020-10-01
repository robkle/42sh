/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   auto_open_path.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihwang <ihwang@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/27 13:47:23 by marvin            #+#    #+#             */
/*   Updated: 2020/10/01 21:33:56 by ihwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "auto_completion.h"

// DIR			*get_dirp(t_auto *auto_com)
// {
// 	char	path[PATH_MAX];
// 	DIR		*dirp;

// 	dirp = NULL;
// 	if (auto_com->status & AUTO_STAT_ROOT)
// 	{
// 		dirp = opendir(auto_com->full_path);
// 	}
// 	else
// 	{

// 	}
// 	auto_com->path;
// 	ft_strcpy(path, auto_com->path);
// 	if (auto_com->status & AUTO_STAT_DIR)
// 	{
// 		ft_strcat(path, "/");
// 		ft_strcat(path, auto_com->word);
// 	}
// 	if ((dirp = opendir((const char*)path)))
// 	{
//         set_status_open(&auto_com->status);
// 		return (dirp);
// 	}
// 	return (NULL);
// }

char            get_list_and_count(t_auto *auto_com)
{
    t_list      *iter;
    int         count;
    DIR     	*dirp;

//	if ((dirp = get_dirp(auto_com)) == NULL)
	//	return (0);
	dirp = opendir(auto_com->full_path);
    auto_get_list(auto_com, dirp);
    closedir(dirp);
    iter = auto_com->list;
    count = 0;
    while (iter != NULL)
    {
        count++;
        iter = iter->next;
    }
   if (count > 0)
       set_status_word_in_path(&auto_com->status);
    return (count);
}

void		auto_open_path(t_l *l)
{
	int		count;

	count = get_list_and_count(&l->auto_com);
	if (count == 0)
		return ;
	else if (count > 1)
	{
		set_status_other_possibility(&l->auto_com.status);
		auto_other_possibility(l);
	}
    else
		auto_no_other_possibility(l);
}

