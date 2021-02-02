/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ctrl_up_down.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthan <dthan@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/20 00:16:56 by ihwang            #+#    #+#             */
/*   Updated: 2021/01/28 13:56:48 by dthan            ###   ########.fr       */
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
	}
	return (EXIT_SUCCESS);
}

int				ctrl_down(t_l *l)
{
	if (l->rs)
		ft_reverse_search_reset(l);
	if ((l->co * (l->y + 1)) + l->x > l->nb + l->pmpt)
	{
		if (l->co - l->x <= l->nb + l->pmpt - (l->x + (l->y * l->co)))
		{
			apply_termcap_str("do", 0, 0);
			l->y++;
		}
		apply_termcap_str("ch", 0, (l->nb + l->pmpt) - (l->y * l->co));
		l->x = (l->nb + l->pmpt) - (l->y * l->co);
	}
	else
	{
		apply_termcap_str("do", 0, 0);
		apply_termcap_str("ch", 0, l->x);
		l->y++;
	}
	return (EXIT_SUCCESS);
}
