/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   auto_file_one_case.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthan <dthan@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/27 13:47:17 by marvin            #+#    #+#             */
/*   Updated: 2020/12/27 17:49:08 by dthan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int			auto_complete_cmd_file(t_auto *auto_com)
{
    char    *word_to_fulfill;
	char	*complete_word;

	complete_word = (char*)auto_com->list->content;
    word_to_fulfill = complete_word + ft_strlen(auto_com->target_str);
    paste(auto_com->editor, NULL, 0, word_to_fulfill);
	if (complete_word[ft_strlen(complete_word) - 1] != '/')
		auto_add_one_extra_char(auto_com->editor, ' ');
	return (clear_auto_struct(auto_com));
}

char		*get_completed_target_str(t_auto *auto_com)
{
	ft_strdel(&auto_com->typed_str);
    auto_com->typed_str = auto_get_typed_str(auto_com->editor);
	return (auto_get_target_str(auto_com));
}

int			auto_file_one_case(t_auto *auto_com)
{
	// char	*completed_target;

	if (!(auto_com->status & AUTO_STAT_COMPLETED))
		return (auto_complete_cmd_file(auto_com));
	return (clear_auto_struct(auto_com));
	// completed_target = get_completed_target_str(auto_com);
	// if (!(auto_is_dir(auto_com->full_path, completed_target)))
	// 	auto_add_one_extra_char(auto_com->editor, ' ');
	// set_status_completed(&auto_com->status);
	// ft_bzero(auto_com->full_path, PATH_MAX);
	// ft_lstdel_strdel(&auto_com->list);
	// auto_com->count_list = 0;
	// ft_strdel(&completed_target);
	// auto_add_one_extra_char(auto_com->editor, ' ');
	// return (clear_auto_struct(auto_com));
}
