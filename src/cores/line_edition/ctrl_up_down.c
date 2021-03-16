/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ctrl_up_down.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthan <dthan@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/20 00:16:56 by ihwang            #+#    #+#             */
/*   Updated: 2021/03/15 09:59:56 by rklein           ###   ########.fr       */
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
		if (l->x > ft_atoi(l->lc[l->y]) - 1)//NEW
		{
			l->x = ft_atoi(l->lc[l->y]) - 1;//NEW
			apply_termcap_str("ch", 0, l->x);//NEW
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
	//OLD
	/*if ((l->co * (l->y + 1)) + l->x > l->nb + l->pmpt)
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
	}*/
	return (EXIT_SUCCESS);
}
