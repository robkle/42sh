/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   auto_completion.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthan <dthan@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/21 17:13:51 by marvin            #+#    #+#             */
/*   Updated: 2021/01/02 18:29:23 by dthan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

char			auto_is_separator(char c)
{
    return (c == '&' || c == ';' || c == '|');
}

int				auto_is_command(t_l *l)
{
	int			head;
	int			curr;

	curr = l->x + (l->y * l->co) - l->pmpt - 1;
	head = curr;
	if (head < 0)
		return (TRUE);
	while (head > 0 && ft_isalnum(l->line[head]) && \
			!auto_is_separator(l->line[head]) && !ft_isspace(l->line[head]))
		--head;
	while (head > 0 && ft_isspace(l->line[head]))
		--head;
	if ((head == 0 || auto_is_separator(l->line[head])) && \
		l->line[head] != '.' && l->line[head] != '/')	
		return (TRUE);
	else
		return (FALSE);
}

void        auto_reset(t_auto *auto_com)
{
	auto_lstdel_strdel(&auto_com->list);
    ft_strdel(&auto_com->target_str);
    ft_strdel(&auto_com->typed_str);
	ft_memset(auto_com->cwd, 0, PATH_MAX);
	ft_memset(auto_com->full_path, 0, PATH_MAX);
	auto_com->count_list = 0;
	auto_com->largest_content_size = 0;
	auto_com->status = 0;
}

int         auto_complete(t_l *l, t_editor_phase *phase)
{
	int		stat;
	t_auto	auto_com;
	t_editor_phase saved_pharse;

	saved_pharse = *phase;
	*phase = EDTR_PHASE_AUTO;

	ft_bzero(&auto_com, sizeof(t_auto));
	auto_com.status |= AUTO_STAT_NEW_POS;


	// where auto comple tion work
    if ((auto_is_command(l)) == TRUE)
		auto_command(l, &auto_com, phase); // need to inject *phase here
	else
        auto_file(l); // need to inject *phase here


	//delete for memory leaks
	auto_lstdel_strdel(auto_com.list);
	if (auto_com.target_str)
		free(auto_com.target_str);
	if (auto_com.typed_str)
		free(auto_com.typed_str);
	if (*phase != EDTR_STOP)
		*phase = saved_pharse;
	return (1);
}
