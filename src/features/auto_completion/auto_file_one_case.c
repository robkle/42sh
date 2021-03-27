/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   auto_file_one_case.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihwang <ihwang@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/27 13:47:17 by marvin            #+#    #+#             */
/*   Updated: 2021/03/26 01:02:51 by ihwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int			auto_complete_cmd_file(t_auto *auto_com)
{
	char	*word_to_fulfill;
	char	*complete_word;

	complete_word = (char *)auto_com->list->content;
	word_to_fulfill = complete_word + ft_strlen(auto_com->target_str);
	paste(auto_com->editor, NULL, word_to_fulfill);
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
	if (!(auto_com->status & AUTO_STAT_COMPLETED))
		return (auto_complete_cmd_file(auto_com));
	return (clear_auto_struct(auto_com));
}
