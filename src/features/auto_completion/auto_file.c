/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   auto_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihwang <ihwang@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/27 13:47:12 by marvin            #+#    #+#             */
/*   Updated: 2021/03/21 11:12:15 by ihwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

char		*auto_get_typed_str(t_l *l)
{
	int		tail;
	int		head;

	tail = l->x + (l->y * l->co) - l->pmpt;
	if (tail == 0)
		return (ft_strnew(0));
	head = tail;
	while (!ft_iswhite(l->line[--head]) \
	&& !auto_is_separator(l->line[head]) && &l->line[head] != l->line)
		NULL;
	if (&l->line[head] == l->line && \
	(auto_is_separator(l->line[0]) || l->line[0] == ' ') && l->line[1] != ' ')
		return (ft_strsub(l->line, 1, tail - 1));
	else if (&l->line[head] == l->line)
		return (ft_strsub(l->line, head, tail));
	else
		return (ft_strsub(l->line, head + 1, tail - head - 1));
}

void		get_full_path(t_auto *auto_com)
{
	char	*last_slash_pos;

	last_slash_pos = ft_strrchr(auto_com->typed_str, '/');
	if (auto_com->typed_str[0] == '/' && last_slash_pos == auto_com->typed_str)
		ft_strcpy(auto_com->full_path, "/");
	else if (auto_com->typed_str[0] == '/')
	{
		ft_strncpy(auto_com->full_path, auto_com->typed_str,
				(int)(last_slash_pos - auto_com->typed_str));
	}
	else if ((auto_com->status & AUTO_STAT_COMPLETED &&
	auto_com->status & AUTO_STAT_DIR) ||
			last_slash_pos)
	{
		ft_strcpy(auto_com->full_path, auto_com->cwd);
		ft_strcat(auto_com->full_path, "/");
		ft_strncat(auto_com->full_path, auto_com->typed_str,
		(int)(last_slash_pos - auto_com->typed_str + 1));
	}
	else
		ft_strcpy(auto_com->full_path, auto_com->cwd);
}

char		*auto_get_target_str(t_auto *auto_com)
{
	char	*separator;
	int		separator_pos;
	size_t	typed_len;

	typed_len = ft_strlen(auto_com->typed_str);
	separator_pos = 0;
	if ((separator = ft_strrchr(auto_com->typed_str, '/')))
		separator_pos = (int)(separator - auto_com->typed_str) + 1;
	if ((auto_com->status & AUTO_STAT_COMPLETED &&
		auto_com->status & AUTO_STAT_DIR) ||
		separator_pos > 0)
	{
		return (ft_strsub(auto_com->typed_str, separator_pos,
		typed_len - separator_pos));
	}
	else
		return (ft_strdup(auto_com->typed_str));
}

void		get_basic_info(t_auto *auto_com)
{
	if (!auto_com->cwd[0])
		getcwd(auto_com->cwd, PATH_MAX);
	if (auto_com->typed_str)
		ft_strdel(&auto_com->typed_str);
	auto_com->typed_str = auto_get_typed_str(auto_com->editor);
	if (!auto_com->full_path[0])
		get_full_path(auto_com);
	if (auto_com->target_str)
		ft_strdel(&auto_com->target_str);
	auto_com->target_str = auto_get_target_str(auto_com);
}

int			auto_file(t_auto *auto_com)
{
	get_basic_info(auto_com);
	if (access(auto_com->full_path, F_OK) ||
		access(auto_com->full_path, X_OK))
		return (clear_auto_struct(auto_com));
	return (auto_file_open_path(auto_com));
}
