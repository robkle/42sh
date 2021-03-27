/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   auto_open_path.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihwang <ihwang@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/27 13:47:23 by marvin            #+#    #+#             */
/*   Updated: 2021/03/26 01:02:40 by ihwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static char		get_list_and_count(t_auto *auto_com)
{
	DIR			*dirp;
	char		list_status;

	dirp = opendir(auto_com->full_path);
	list_status = auto_get_list(auto_com, dirp);
	closedir(dirp);
	if (list_status == EXIT_FAILURE)
		return (-1);
	return (0);
}

int				auto_file_open_path(t_auto *auto_com)
{
	if (get_list_and_count(auto_com) == -1)
		return (clear_auto_struct(auto_com));
	if (auto_com->count_list <= 0)
	{
		ft_beep_sound();
		return (clear_auto_struct(auto_com));
	}
	else if (auto_com->count_list > 1)
		return (auto_cmd_file_multiple_cases(auto_com));
	else
		return (auto_file_one_case(auto_com));
}
