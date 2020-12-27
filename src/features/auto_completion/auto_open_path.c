/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   auto_open_path.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthan <dthan@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/27 13:47:23 by marvin            #+#    #+#             */
/*   Updated: 2020/12/27 17:49:48 by dthan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

size_t			get_count(t_auto *auto_com)
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
				((ft_strequ(content, "./") ||ft_strequ(content, "../")) && \
				(ft_strequ(target_str, ".") || ft_strequ(target_str, ".."))))
			count++;
		iter = iter->next;
	}
	return (count);
}

void			prune_list_for_single_file(t_auto *auto_com)
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

void			prune_list_for_multiple_files(t_auto *auto_com)
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
			{
				auto_com->list = p_list;
				return ;
			}
			p_list = temp_list;
		}
	}
}

void			prune_list(t_auto *auto_com, size_t count)
{
	if (count == 1)
		prune_list_for_single_file(auto_com);
	else if (count > 1)
		prune_list_for_multiple_files(auto_com);
}

static char		get_list_and_count(t_auto *auto_com)
{
    size_t		count;
    DIR     	*dirp;

	dirp = opendir(auto_com->full_path);
	auto_get_list(auto_com, dirp);
	closedir(dirp);
	count = get_count(auto_com);
	prune_list(auto_com, count);
	return (count);
}

void		auto_file_open_path(t_l *l)
{
	size_t	count;

	count = get_list_and_count(&l->auto_com);
	if (count == 0)
	{
		ft_beep_sound();
		return ;
	}
	else if (count > 1)
	{
		auto_cmd_file_multiple_cases(l);
	}
    else
		auto_file_one_case(l);
}

