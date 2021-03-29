/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reverse_search_row_count.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rklein <rklein@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/27 22:16:25 by rklein            #+#    #+#             */
/*   Updated: 2021/03/29 15:43:51 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static void	ft_init_rs_row_count(t_l *l, char tmp[], int *count)
{
	int		len;
	int		d;

	*count = ft_strlen(l->rev_sr);
	ft_bzero(tmp, 4096);
	if (g_shell.history->hist[g_shell.history->hst][0])
	{
		len = ft_strlen(g_shell.history->hist[g_shell.history->hst]);
		d = 1;
		ft_strncpy(tmp, g_shell.history->hist[g_shell.history->hst], \
		len - d);
	}
	else
		ft_strcpy(tmp, g_shell.history->hist[g_shell.history->hst]);
}

int			ft_row_count_rs(t_l *l)
{
	char	tmp[4096];
	int		i;
	int		count;
	int		row;

	ft_init_rs_row_count(l, tmp, &count);
	i = 0;
	row = 1 + (count / l->co);
	while (tmp[i])
	{
		count++;
		if (tmp[i] == '\n')
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

void		ft_line_count_rs(t_l *l)
{
	char	tmp[4096];
	int		count;
	int		i;
	int		j;

	ft_recalc_lc(l);
	ft_init_rs_row_count(l, tmp, &count);
	i = -1;
	j = 0;
	while (tmp[++i])
	{
		count++;
		if (tmp[i] == '\n')
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
