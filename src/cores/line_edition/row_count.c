/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   row_count.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihwang <ihwang@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/12 19:43:38 by rklein            #+#    #+#             */
/*   Updated: 2021/03/27 22:36:47 by rklein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

/*
**Counts the total number of rows of l->line
*/

int		ft_row_count(t_l *l)
{
	int i;
	int count;
	int row;

	count = l->pmpt;
	i = 0;
	row = 1;
	while (l->line[i])
	{
		count++;
		if (l->line[i] == '\n')
		{
			row++;
			count = 0;
		}
		else if (count == l->co)
		{
			row++;
			count = 0;
		}
		i++;
	}
	return (row);
}

void	ft_recalc_lc(t_l *l)
{
	int row;

	ft_arraydel(l->lc);
	row = l->rs ? ft_row_count_rs(l) : ft_row_count(l);
	l->lc = malloc(sizeof(char*) * (row + 1));
}

void	ft_line_count(t_l *l)
{
	int	count;
	int	i;
	int	j;

	ft_recalc_lc(l);
	count = l->pmpt;
	i = -1;
	j = 0;
	while (l->line[++i])
	{
		count++;
		if (l->line[i] == '\n')
		{
			l->lc[j++] = ft_itoa(count);
			count = 0;
		}
		else if (count == l->co)
		{
			l->lc[j++] = ft_itoa(count);
			count = 0;
		}
	}
	l->lc[j++] = ft_itoa(count % l->co);
	l->lc[j] = NULL;
}
