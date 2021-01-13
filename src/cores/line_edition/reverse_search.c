/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reverse_search.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthan <dthan@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/27 16:47:53 by dthan             #+#    #+#             */
/*   Updated: 2020/12/27 16:47:54 by dthan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static void ft_reverse_search_fail(t_l *l)
{
	char *tmp;

	if (l->rev_sr[1] == 'f')
	{
		tmp = ft_strdup(l->rev_sr);
		ft_bzero(l->rev_sr, ft_strlen(l->rev_sr));
		ft_strcpy(l->rev_sr, "(");
		ft_strcat(l->rev_sr, &tmp[8]);
		free(tmp);
		l->rs_i -= 7;
	}
	else
	{
		tmp = ft_strdup(l->rev_sr);
		ft_bzero(l->rev_sr, ft_strlen(l->rev_sr));
		ft_strcpy(l->rev_sr, "(failed ");
		ft_strcat(l->rev_sr, &tmp[1]);
		free(tmp);
		l->rs_i += 7;
	}
}

static void	ft_reverse_search_scan(t_l *l, char action)
{
	char	*tmp;
	int		i;
	
	tmp = l->rev_sr[1] == 'f' ? ft_strsub(l->rev_sr, 26, l->rs_i - 26) : \
		ft_strsub(l->rev_sr, 19, l->rs_i - 19);
	i = action == 'r' ? g_shell.history->hst - 1 : g_shell.history->hst;
	while (--i > -1)
	{
		if (ft_strstr_int(g_shell.history->hist[i], tmp))
		{	
			g_shell.history->hst = i;
			if (l->rev_sr[1] == 'f')
				ft_reverse_search_fail(l);
			break ;
		}
	}
	if (i == -1 && l->rev_sr[1] != 'f')
		ft_reverse_search_fail(l);
}

void	ft_reverse_search_bs(t_l *l)
{
	if ((l->rev_sr[1] != 'f' && l->rs_i == 19) ||
		(l->rev_sr[1] == 'f' && l->rs_i == 26))
		return ;
	else
	{
		l->rs_i--;
		ft_memmove(l->rev_sr + l->rs_i, l->rev_sr + l->rs_i + 1, \
			ft_strlen(l->rev_sr + l->rs_i));
		l->rev_sr[ft_strlen(l->rev_sr)] = 0;
		if (((l->rev_sr[1] != 'f' && ft_strlen(l->rev_sr) > 22) ||
			(l->rev_sr[1] == 'f' && ft_strlen(l->rev_sr) > 29)) && g_shell.history->hst)
			ft_reverse_search_scan(l, 'a');
		ft_reverse_search_clear(l);
		ft_putstr(l->rev_sr);
		ft_putstr(g_shell.history->hist[g_shell.history->hst]);
	}
}

void		ft_reverse_search_add(char t[], t_l *l)
{

	ft_memmove(l->rev_sr + l->rs_i + 1, l->rev_sr + l->rs_i, \
		ft_strlen(l->rev_sr + l->rs_i));
	l->rev_sr[l->rs_i++] = t[0];
	ft_reverse_search_scan(l, 'a');
	ft_reverse_search_clear(l);
	ft_putstr(l->rev_sr);
	ft_putstr(g_shell.history->hist[g_shell.history->hst]);
}

int		ft_reverse_search(t_l *l)
{
	if (!l->rs)
	{
		if (!l->line)
			l->line = ft_strnew(0);
		ft_reverse_search_clear(l);
		l->rs = 1;
		l->rev_sr = ft_memalloc(4096);
		ft_strcpy(l->rev_sr, "(reverse-i-search)`': ");
		l->rs_i = 19;
	}
	else if (ft_strlen(l->rev_sr) > 22 && l->rev_sr[1] != 'f')
	{
			if (g_shell.history->hst)
				ft_reverse_search_scan(l, 'r');
	}
	ft_reverse_search_clear(l);
	ft_putstr(l->rev_sr);
	ft_putstr(g_shell.history->hist[g_shell.history->hst]);
	return EXIT_SUCCESS;
}
