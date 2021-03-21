/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   auto_prune_list.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihwang <ihwang@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/21 13:55:52 by ihwang            #+#    #+#             */
/*   Updated: 2021/03/21 13:56:41 by ihwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static void		prune_list_for_single_file(t_auto *auto_com)
{
	char		*target_str;
	t_list		*p_list;
	t_list		*temp_list;

	target_str = auto_com->target_str;
	p_list = auto_com->list;
	if (target_str[0] == '\0')
	{
		while (p_list)
		{
			temp_list = p_list->next;
			if (ft_strequ((char*)p_list->content, "./") || \
				ft_strequ((char*)p_list->content, "../"))
			{
				ft_memdel(&p_list->content);
				free(p_list);
			}
			else
				auto_com->list = p_list;
			p_list = temp_list;
		}
		auto_com->list->next = NULL;
	}
}

static void		prune_list_for_multiple_files(t_auto *auto_com)
{
	char		*target_str;
	t_list		*p_list;
	t_list		*temp_list;

	target_str = auto_com->target_str;
	p_list = auto_com->list;
	if ((!ft_strequ(target_str, "../") && !ft_strequ(target_str, "./")))
	{
		while (p_list)
		{
			temp_list = p_list->next;
			if (ft_strequ((char*)p_list->content, "./") || \
				ft_strequ((char*)p_list->content, "../"))
			{
				ft_memdel(&p_list->content);
				free(p_list);
			}
			else
				break ;
			p_list = temp_list;
		}
	}
	auto_com->list = p_list;
}

void			auto_prune_list(t_auto *auto_com, size_t count)
{
	if (count == 1)
		prune_list_for_single_file(auto_com);
	else if (count > 1)
		prune_list_for_multiple_files(auto_com);
}
