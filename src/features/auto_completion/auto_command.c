/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   auto_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihwang <ihwang@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/11 10:33:21 by marvin            #+#    #+#             */
/*   Updated: 2021/03/21 04:27:49 by ihwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void			get_single_path(\
	char single_path[], char *path_env, size_t *head, size_t *tail)
{
	*head = *tail;
	while (path_env[*tail] != ':' && path_env[*tail] != '\0')
		(*tail)++;
	ft_strncpy(single_path, &path_env[*head], *tail - *head);
	single_path[*tail - *head] = '\0';
	(*tail)++;
}

char			is_duplicated_cmd(t_list *list, char *cmd)
{
	while (list)
	{
		if (ft_strequ((char *)list->content, cmd))
			return (TRUE);
		list = list->next;
	}
	return (FALSE);
}

void			make_list(char path[], t_auto *auto_com)
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

static size_t	get_count(t_auto *auto_com)
{
	t_list		*iter;
	size_t		count;
	size_t		target_str_len;
	char		*target_str;

	count = 0;
	target_str_len = ft_strlen(auto_com->target_str);
	iter = auto_com->list;
	target_str = auto_com->target_str;
	while (iter)
	{
		if (ft_strnequ((char *)iter->content, target_str, target_str_len))
		{
			if (ft_strlen((char *)iter->content) > auto_com->longest_len)
			{
				auto_com->longest_len = ft_strlen((char *)iter->content);
				auto_com->longest = iter->content;
			}
			count++;
		}
		iter = iter->next;
	}
	return (count);
}

void			get_cmd_list(t_auto *auto_com)
{
	size_t		head;
	size_t		tail;
	size_t		path_env_len;
	char		path[PATH_MAX];

	head = 0;
	tail = 0;
	auto_com->path_env = ft_getenv("PATH");
	if (auto_com->path_env == NULL)
		return ;
	path_env_len = ft_strlen(auto_com->path_env);
	while (tail < path_env_len)
	{
		get_single_path(path, auto_com->path_env, &head, &tail);
		if (!(access(path, F_OK) || access(path, X_OK)))
			make_list(path, auto_com);
	}
}

static void		get_basic_info(t_auto *auto_com)
{
	auto_com->path_env = ft_getenv("PATH");
	if (auto_com->typed_str)
		ft_strdel(&auto_com->typed_str);
	auto_com->typed_str = auto_get_typed_str(auto_com->editor);
	if (auto_com->target_str)
		ft_strdel(&auto_com->target_str);
	auto_com->target_str = auto_get_target_str(auto_com);
}

int				auto_command(t_auto *auto_com)
{
	get_basic_info(auto_com);
	get_cmd_list(auto_com);
	auto_com->count_list = get_count(auto_com);
	if (auto_com->count_list == 0)
	{
		ft_beep_sound();
		return (clear_auto_struct(auto_com));
	}
	else if (auto_com->count_list > 1)
		return (auto_cmd_file_multiple_cases(auto_com));
	else
		return (auto_complete_cmd_file(auto_com));
}
