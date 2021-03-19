/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   left_right_bs_key.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthan <dthan@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/20 00:13:02 by ihwang            #+#    #+#             */
/*   Updated: 2021/03/19 22:46:33 by rklein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static void	bs_key_str(t_l *l)
{
	int				i;
	int				index;

	if (l->y == 0)
	{
		ft_putstr(&l->line[l->x - l->pmpt]);
		i = l->x - 2 - l->pmpt;
		l->x--;
	}
	else
	{
		index = ft_index_calc(l);
		ft_putstr(&l->line[index]);
		i = index - 2;
		if (l->x == 0)
		{
			l->y--;
			l->x = ft_atoi(l->lc[l->y]) - 1;
		}
		else
			l->x--;
	}
	while (++i < l->nb)
		l->line[i] = l->line[i + 1];
	l->nb--;
}

int			bs_key(t_l *l)
{
	if (l->rs)
		ft_reverse_search_bs(l);
	else
	{
		if (l->y == 0 && l->x == l->pmpt)
			return (EXIT_SUCCESS);
		if (l->x == 0 && l->y != 0)
		{
			apply_termcap_str("up", 0, 0);
			apply_termcap_str("ch", 0, ft_atoi(l->lc[l->y - 1]) - 1);
		}
		else
			apply_termcap_str(LEFT, 0, 0);
		apply_termcap_str("cd", 0, 0);
		apply_termcap_str("sc", 0, 0);
		bs_key_str(l);
		apply_termcap_str("rc", 0, 0);
	}
	return (EXIT_SUCCESS);
}

int			left_key(t_l *l)
{
	if (l->rs)
		ft_reverse_search_reset(l);
	if (l->x == l->pmpt && l->y == 0)
		return (EXIT_SUCCESS);
	if (l->x == 0 && l->y != 0)
	{
		l->y--;
		l->x = ft_atoi(l->lc[l->y]) - 1;
		apply_termcap_str("up", 0, 0);
		apply_termcap_str("ch", 0, ft_atoi(l->lc[l->y]) - 1);
	}
	else
	{
		apply_termcap_str("#4", 0, 0);
		l->x--;
	}
	return (EXIT_SUCCESS);
}

int			right_key(t_l *l)
{
	int	i;

	if (l->rs)
		ft_reverse_search_reset(l);
	i = ft_index_calc(l);
	if (i == l->nb)
		return (EXIT_SUCCESS);
	if ((l->x != ft_atoi(l->lc[l->y]) - 1) || \
	(l->x == ft_atoi(l->lc[l->y]) - 1 && !l->lc[l->y + 1]))
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
