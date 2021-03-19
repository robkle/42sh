/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ctrl_up_down.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthan <dthan@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/20 00:16:56 by ihwang            #+#    #+#             */
/*   Updated: 2021/03/19 21:58:58 by rklein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int				ctrl_up(t_l *l)
{
	if (l->rs)
		ft_reverse_search_reset(l);
	if (l->y == 0)
	{
		apply_termcap_str("ch", 0, l->pmpt);
		l->x = l->pmpt;
	}
	else if (l->y == 1 && l->x < 3)
	{
		apply_termcap_str("up", 0, 0);
		apply_termcap_str("ch", 0, l->pmpt);
		l->y = 0;
		l->x = l->pmpt;
	}
	else
	{
		apply_termcap_str("up", 0, 0);
		l->y--;
		if (l->x > ft_atoi(l->lc[l->y]) - 1)
		{
			l->x = ft_atoi(l->lc[l->y]) - 1;
			apply_termcap_str("ch", 0, l->x);
		}
	}
	return (EXIT_SUCCESS);
}

int				ctrl_down(t_l *l)
{
	if (l->rs)
		ft_reverse_search_reset(l);
	if (l->lc[l->y + 1])
	{
		apply_termcap_str("do", 0, 0);
		l->y++;
		if (ft_atoi(l->lc[l->y]) < l->x)
		{
			l->x = ft_atoi(l->lc[l->y]);
			apply_termcap_str("ch", 0, l->x);
		}
		else
			apply_termcap_str("ch", 0, l->x);
	}
	else
	{
		l->x = ft_atoi(l->lc[l->y]);
		apply_termcap_str("ch", 0, l->x);
	}
	return (EXIT_SUCCESS);
}
