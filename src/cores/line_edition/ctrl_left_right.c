/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ctrl_left_right.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthan <dthan@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/20 00:15:39 by ihwang            #+#    #+#             */
/*   Updated: 2021/03/19 22:20:49 by rklein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static int	ctrl_right_pos_check(char *line, int index)
{
	if (index == 0)
		return (1);
	if (ft_isspace(line[index - 1]))
		return (1);
	return (0);
}

int			ctrl_right(t_l *l)
{
	int	index;

	index = ft_index_calc(l);
	if (index < l->nb && !ft_isspace(l->line[index]) && \
	ctrl_right_pos_check(l->line, index))
	{
		right_key(l);
		index++;
	}
	while (index < l->nb && !(!ft_isspace(l->line[index]) && \
	ctrl_right_pos_check(l->line, index)))
	{
		right_key(l);
		index++;
	}
	return (EXIT_SUCCESS);
}

int			ctrl_left(t_l *l)
{
	int	i;
	int	index;

	i = 0;
	while (ft_isspace(l->line[i]))
		i++;
	index = ft_index_calc(l);
	if (index > i && !ft_isspace(l->line[index]) && \
	ft_isspace(l->line[index - 1]))
	{
		left_key(l);
		index--;
	}
	while (index > i && !(!ft_isspace(l->line[index]) && \
	ft_isspace(l->line[index - 1])))
	{
		left_key(l);
		index--;
	}
	return (EXIT_SUCCESS);
}
