/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   row_count.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihwang <ihwang@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/12 19:43:38 by rklein            #+#    #+#             */
/*   Updated: 2021/03/26 14:57:20 by rklein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

/*
**Counts the total number of rows of l->line
*/

int			ft_row_count_rs(t_l *l)
{
	char	tmp[4096];//NEW
	int		len;//NEW
	int		d;//NEW
	int i;
	int count;
	int row;

	count = ft_strlen(l->rev_sr);
	ft_bzero(tmp, 4096);//NEW
	if (g_shell.history->hist[g_shell.history->hst][0])
	{
		len = ft_strlen(g_shell.history->hist[g_shell.history->hst]);//NEW
		d = g_shell.history->hist[g_shell.history->hst][len - 1] == 4 ? 2 : 1;//NEW
		ft_strncpy(tmp, g_shell.history->hist[g_shell.history->hst], \
		len - d);//NEW
	}
	else
		ft_strcpy(tmp, g_shell.history->hist[g_shell.history->hst]);
	i = 0;
	row = 1 + count / l->co;
	//while (g_shell.history->hist[g_shell.history->hst][i])
	while (tmp[i])
	{
		count++;
		//if (g_shell.history->hist[g_shell.history->hst][i] == '\n')
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

int			ft_row_count(t_l *l)
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

static void	ft_recalc_lc(t_l *l)
{
	int row;

	ft_arraydel(l->lc);
	row = ft_row_count(l);
	l->lc = malloc(sizeof(char*) * (row + 1));
}

void		ft_line_count_rs(t_l *l)
{
	char	tmp[4096];//NEW
	int		len;//NEW
	int		d;//NEW
	int		count;
	int		i;
	int		j;

	ft_recalc_lc(l);
	ft_bzero(tmp, 4096);//NEW
	if (g_shell.history->hist[g_shell.history->hst][0])
	{
		len = ft_strlen(g_shell.history->hist[g_shell.history->hst]);//NEW
		d = g_shell.history->hist[g_shell.history->hst][len - 1] == 4 ? 2 : 1;//NEW
		ft_strncpy(tmp, g_shell.history->hist[g_shell.history->hst], \
		len - d);//NEW
	}
	else
		ft_strcpy(tmp, g_shell.history->hist[g_shell.history->hst]);
		
	count = ft_strlen(l->rev_sr);
	i = -1;
	j = 0;
	//while (g_shell.history->hist[g_shell.history->hst][++i])
	while (tmp[++i])//NEW
	{
		count++;
		//if (g_shell.history->hist[g_shell.history->hst][i] == '\n')
		if (tmp[i] == '\n')//NEW
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

void		ft_line_count(t_l *l)
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
