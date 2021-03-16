/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   home_end_key.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthan <dthan@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/20 00:10:13 by ihwang            #+#    #+#             */
/*   Updated: 2021/03/13 16:52:19 by rklein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int					home_key(t_l *l)
{
	int				i;

	if (l->rs)
		ft_reverse_search_reset(l);
	i = l->y;
	while (i--)
		apply_termcap_str("up", 0, 0);
	apply_termcap_str("ch", 0, l->pmpt);
	l->x = l->pmpt;
	l->y = 0;
	return (EXIT_SUCCESS);
}

int					end_key(t_l *l)
{
	int				i;

	if (l->rs)
		ft_reverse_search_reset(l);
	home_key(l);
	i = 0;
	while (++i <= l->nb)
		right_key(l);
	/*l->y = (l->nb + l->pmpt) / l->co;//OLD
	//l->y = ft_row_count(l) - 1;//NEW
	l->x = (l->nb + l->pmpt) % l->co;//OLD
	//l->x = ft_cursor_x(l);//NEW
	i = l->y;
	while (i--)
		apply_termcap_str("do", 0, 0);
	apply_termcap_str("ch", 0, l->x);*/
	return (EXIT_SUCCESS);
}
