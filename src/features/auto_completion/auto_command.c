/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   auto_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthan <dthan@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/11 10:33:21 by marvin            #+#    #+#             */
/*   Updated: 2020/12/27 17:48:45 by dthan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void			get_single_path( \
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
		if (ft_strequ((char*)list->content, cmd))
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
			node = ft_lstnew_str((void*)dir->d_name, ft_strlen(dir->d_name));
			if (auto_com->list == NULL)
				auto_com->list = node;
			else
				auto_add_list_on_spot(auto_com, node);
		}
	}
	closedir(dirp);
}

static size_t			get_count(t_auto *auto_com)
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
		if (ft_strnequ((char*)iter->content, target_str, target_str_len))
		{
			if (ft_strlen((char*)iter->content) > auto_com->largest_content_size)
			{
				auto_com->largest_content_size = ft_strlen((char*)iter->content);
				auto_com->largest_content = iter->content;
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
	auto_com->path_env[105] = 0;
	path_env_len = ft_strlen(auto_com->path_env);
	while (tail < path_env_len)
	{
		get_single_path(path, auto_com->path_env, &head, &tail);
		if (!(access(path, F_OK) || access(path, X_OK)))
			make_list(path, auto_com);
	}
}

static void		get_basic_info(t_l *l)
{
	l->auto_com.path_env = get_var("PATH", g_shell.env, VAL);
	if (l->auto_com.typed_str)
		ft_strdel(&l->auto_com.typed_str);
	l->auto_com.typed_str = auto_get_typed_str(l);
	if (l->auto_com.target_str)
		ft_strdel(&l->auto_com.target_str);
	l->auto_com.target_str = auto_get_target_str(&l->auto_com);
}

void		auto_command(t_l *l)
{
	get_basic_info(l);
	get_cmd_list(&l->auto_com);
	l->auto_com.count_list = get_count(&l->auto_com);
	if (l->auto_com.count_list == 0)
	{
		ft_beep_sound();
		return ;
	}
	else if (l->auto_com.count_list > 1)
		auto_cmd_file_multiple_cases(l);
	else
	{
		auto_complete_cmd_file(l);
		auto_add_one_extra_char(l, ' ');
	}
}