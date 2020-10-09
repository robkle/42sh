/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihwang <ihwang@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/20 00:22:24 by ihwang            #+#    #+#             */
/*   Updated: 2020/08/05 05:42:59 by tango            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void		get_history(int fd)
{
/* currently this only reads one line per hist string. modify to 
** take into account multi line commands by using buffer
*/
	char	*line;
	//char	*buffer;
	int		i;

	fd = open("./.history", O_RDWR | O_CREAT, 0644);
	//buffer = ft_memalloc(4096);//change to ARG_MAX
	i = 0;
	while (get_next_line(fd, &line))	
	{
		g_h->hist[i++] = ft_strdup(line);
		g_h->curr = i;
	}
	g_h->hist[i] = ft_strnew(0);
	g_h->hst = g_h->curr;
	close(fd);
}

void		append_history(t_l *l)
{
	int	i;

	if (!l->line || !ft_isprint(l->line[0]))
		return ;
	if (g_h->curr < HISTFILESIZE)
	{
		free(g_h->hist[g_h->curr]);
		g_h->hist[g_h->curr++] = ft_strdup(l->line);
		g_h->hist[g_h->curr] = ft_strnew(0);
	}
	else
	{
		i = 0;
		free(g_h->hist[i]);
		while (i < HISTFILESIZE - 1)
		{
			g_h->hist[i] = g_h->hist[i + 1];
			i++;
		}
		free(g_h->hist[i]);
		g_h->hist[i] = ft_strdup(l->line);
	}
	delete_save_history(); //history file update after each command.
}

void		delete_save_history(void)
{
	int		i;
	int		fd;

	if (g_h->curr == 0)
		return ;
	fd = open("./.history", O_RDWR);
	i = -1;
	while (++i < g_h->curr)
	{
		write(fd, g_h->hist[i], ft_strlen(g_h->hist[i]));
		if (i + 1 < g_h->curr)
			write(fd, "\n", 1);
	}
	close(fd);
}
