#include "shell.h"

static int		ft_reverse_search_count_rows(t_l *l)
{
	int	count;
	int	row;
	int	i;

	count = ft_strlen(l->rev_sr);
	row = count / l->co;
	i = -1;
	while (g_h->hist[g_h->hst][++i])
	{
		if(g_h->hist[g_h->hst][i] == '\n')
		{
			row++;
			count = 0;
		}
		row += count / l->co;
		count++;
	}
	l->nb = count;
	l->y = row;
	l->x = count % l->co;
	return (row);
}

static void			ft_reverse_search_clear(t_l *l)
{
	int				i;
	int				line_rows;
	int				starting_row_from_top;
	int				new_starting_row;

	line_rows = l->rs ? ft_reverse_search_count_rows(l) : ft_count_rows(l);
	new_starting_row = l->starting_row;
	if (l->starting_row < line_rows)
		new_starting_row = line_rows;
	starting_row_from_top = l->total_row - l->starting_row;
	i = get_current_row() - starting_row_from_top;//ft in term_attr.c
	while (i-- > 0)
		apply_termcap_str("up", 0, 0);
	apply_termcap_str("ch", 0, 0);
	apply_termcap_str("cd", 0, 0);
	l->starting_row = new_starting_row;
}

static void	ft_reverse_search_scan(t_l *l, char action)
{
	char	*tmp;
	int		i;
	
	tmp = ft_strsub(l->rev_sr, 19, l->rs_i - 19);
	i = action == 'r' ? g_h->hst - 1 : g_h->hst;
	while (--i > -1)
	{
		if (ft_strstr_int(g_h->hist[i], tmp))
		{	
			g_h->hst = i;
			break ;
		}
	}
	if (i == -1)
	{
		free(tmp);
		tmp = ft_strdup(l->rev_sr);
		ft_bzero(l->rev_sr, ft_strlen(l->rev_sr));
		ft_strcpy(l->rev_sr, "(failed ");
		ft_strcat(l->rev_sr, &tmp[1]);
		free(tmp);
		l->rs_i += 7;
		
	}
}

void		ft_reverse_search_add(char t[], t_l *l)
{

	ft_memmove(l->rev_sr + l->rs_i + 1, l->rev_sr + l->rs_i, \
		ft_strlen(l->rev_sr + l->rs_i));
	l->rev_sr[l->rs_i++] = t[0];
	if (l->rev_sr[1] != 'f')
		ft_reverse_search_scan(l, 'a');
	ft_reverse_search_clear(l);
	ft_putstr(l->rev_sr);
	ft_putstr(g_h->hist[g_h->hst]);
}

void	ft_reverse_search(t_l *l)
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
			if (g_h->hst)
				ft_reverse_search_scan(l, 'r');
	}
	ft_reverse_search_clear(l);
	ft_putstr(l->rev_sr);
	ft_putstr(g_h->hist[g_h->hst]);
}
