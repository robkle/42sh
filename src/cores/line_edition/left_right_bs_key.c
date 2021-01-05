/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   left_right_bs_key.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthan <dthan@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/20 00:13:02 by ihwang            #+#    #+#             */
/*   Updated: 2021/01/05 15:56:16 by dthan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static void			bs_key_str(t_l *l)
{
	int				i;

	if (l->y == 0)
	{
		ft_putstr(&l->line[l->x - l->pmpt]);
		i = l->x - 2 - l->pmpt;
		l->x--;
	}
	else
	{
		ft_putstr(&l->line[l->x + (l->co * l->y) - l->pmpt]);
		i = l->x + (l->co * l->y) - 2 - l->pmpt;
		if (l->x == 0)
		{
			l->x = l->co - 1;
			l->y--;
		}
		else
			l->x--;
	}
	while (++i < l->nb)
		l->line[i] = l->line[i + 1];
	l->nb--;
}

int					bs_key(t_l *l)
{
	if (l->rs) // later
		ft_reverse_search_bs(l); // later
	else
	{
		if (l->y == 0 && l->x == l->pmpt)
			// return (1);
			return (EXIT_SUCCESS);
		if (l->x == 0 && l->y != 0)
		{
			apply_termcap_str("up", 0, 0);
			apply_termcap_str("ch", 0, l->co);
		}
		else
			apply_termcap_str(LEFT, 0, 0);
		apply_termcap_str("cd", 0, 0);
		apply_termcap_str("sc", 0, 0);
		bs_key_str(l);
		apply_termcap_str("rc", 0, 0);
	}
	// return (1);
	return (EXIT_SUCCESS);
}

int				left_key(t_l *l)
{
	if (l->rs)
		ft_reverse_search_reset(l);
	if (l->x == l->pmpt && l->y == 0)
		return (EXIT_SUCCESS);
	if (l->x == 0 && l->y != 0)
	{
		l->y--;
		l->x = l->co - 1;
		apply_termcap_str("up", 0, 0);
		apply_termcap_str("ch", 0, l->co - 1);
	}
	else
	{
		apply_termcap_str("#4", 0, 0);
		l->x--;
	}
	return (EXIT_SUCCESS);
}

int				right_key(t_l *l)
{
	if (l->rs)
		ft_reverse_search_reset(l);
	if (l->x + (l->y * l->co) - l->pmpt == l->nb)
		return EXIT_SUCCESS;
	if (l->x != l->co - 1)
	{
		apply_termcap_str("nd", 0, 0);
		l->x++;
	}
	else
	{
		apply_termcap_str("do", 0, 0);
		l->x = 0;
		l->y++;
	}
	return (EXIT_SUCCESS);
}
