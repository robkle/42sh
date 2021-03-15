/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   row_count.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rklein <rklein>                            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/12 19:43:38 by rklein            #+#    #+#             */
/*   Updated: 2021/03/15 16:40:13 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

// Calculates the row in which the given index
int		ft_y_pos(t_l *l, int index)
{
	int i;
	int	count;
	int	row;

	count = l->pmpt;
	i = 0;
	row = 1;
	while (l->line[i] && i <= index)
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

/*Counts the total number of rows of l->line*/ 
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

void	ft_line_count(t_l *l)
{
	int	count;
	int row;
	int	i;
	int	j;
	
	ft_arraydel(l->lc);
	row = ft_row_count(l);
	l->lc = malloc(sizeof(char*) * row + 1);
	count = l->pmpt;
	i = 0;
	j = 0;
	while (l->line[i])
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
		i++;
	}
	l->lc[j++] = ft_itoa(count % l->co);
	l->lc[j] = NULL;
}

/*
** calculates the index of l->line on which the cursor is
**/
int		ft_index_calc(t_l *l)
{
	int	i;
	int len;
	
	len = l->x;
	i = l->y;
	while (--i >= 0)
	{
		len += ft_atoi(l->lc[i]);
	}
	return (len - l->pmpt);
}

/*
** calculates the x position of cursor for history command
*/
int		ft_cursor_x(t_l *l)
{
	int	i;

	ft_line_count(l);
	i = 0;
	while (l->lc[i])
		i++;
	return (ft_atoi(l->lc[i - 1]));
}
