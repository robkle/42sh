/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   auto_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihwang <ihwang@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/27 13:47:12 by marvin            #+#    #+#             */
/*   Updated: 2020/10/11 09:02:24 by ihwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "auto_completion.h"

char        *auto_get_typed_str(t_l *l)
{
    int     tail;
    int     head;

    tail = l->x + (l->y * l->co) - l->pmpt;
    head = tail;
    while (!ft_iswhite(l->line[--head]))
        NULL;
	//Sev fault here.
	return (ft_strsub(l->line, head + 1, tail - head - 1));
	//return (ft_strndup(&l->line[head + 1], tail - head - 1));
	//l->auto_com->typed = ft_strndup(&l->line[head + 1], tail - head);
}

void        get_full_path(t_auto *auto_com)
{
	char	*last_slash_pos;

	last_slash_pos = ft_strrchr(auto_com->typed_str, '/');
	if (auto_com->typed_str[0] == '/')
	{
		if (last_slash_pos == auto_com->typed_str)
			ft_strcpy(auto_com->full_path, "/");
		else
			ft_strncpy(auto_com->full_path, auto_com->typed_str, \
			(int)(last_slash_pos - auto_com->typed_str));
	}
	else if ((auto_com->status & AUTO_STAT_COMPLETED && \
			auto_com->status & AUTO_STAT_DIR) \
			|| last_slash_pos)
	{
		ft_strcpy(auto_com->full_path, auto_com->cwd);
		ft_strcat(auto_com->full_path, "/");
		ft_strncat(auto_com->full_path, auto_com->typed_str, \
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
	if ((auto_com->status & AUTO_STAT_COMPLETED && \
		auto_com->status & AUTO_STAT_DIR) || separator_pos > 0)
	{
		return (ft_strsub(auto_com->typed_str, separator_pos, \
				typed_len - separator_pos));
	}
	else
		return (ft_strdup(auto_com->typed_str));
}

char        has_access(char *full_path)
{
	if (access(full_path, F_OK))
		return (FALSE);
	else if (access(full_path, X_OK))
		return (FALSE);
    return (TRUE);
}

void        auto_file(t_l *l)
{
	if (!l->auto_com.cwd[0])
		getcwd(l->auto_com.cwd, PATH_MAX);
    if (l->auto_com.typed_str)
        ft_strdel(&l->auto_com.typed_str);
    l->auto_com.typed_str = auto_get_typed_str(l);
    if (!l->auto_com.full_path[0])
		get_full_path(&l->auto_com);
	if (l->auto_com.target_str)
		ft_strdel(&l->auto_com.target_str);
	l->auto_com.target_str = auto_get_target_str(&l->auto_com);
    if (has_access(l->auto_com.full_path))
        return (auto_open_path(l));
	else
		auto_reset(&l->auto_com);
}
