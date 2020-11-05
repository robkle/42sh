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

void			ft_reverse_search_clear(t_l *l)
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
	
void	ft_reverse_search_reset(t_l *l)
{
	free(l->rev_sr);
	l->rs = 0;
	free(l->line);
	l->line = ft_strdup(g_h->hist[g_h->hst]);
	ft_reverse_search_clear(l);
	ft_putstr("> ");
	ft_putstr(l->line);
	home_key(l);	
}
