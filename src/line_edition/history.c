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
	char	*line;
	char	*buffer;
	int		i;

	fd = open("./.history", O_RDWR | O_CREAT, 0644);
	buffer = ft_memalloc(4096);//change to ARG_MAX
	i = 0;
	while (get_next_line(fd, &line) && i <= HISTFILESIZE)	
	{
		ft_strcat(buffer, line);
		if (!ft_check_cont(buffer))
		{
			g_h->hist[i++] = ft_strdup(buffer);
			g_h->curr = i;
			ft_bzero(buffer, ft_strlen(buffer));
		}
		else
			ft_strcat(buffer, "\n");
	}
	g_h->hst = g_h->curr;
	g_h->hist[i++] = ft_strnew(0);
	g_h->hist[i] = NULL;
	free(buffer);
	close(fd);
}

void		append_history(char *line)
{
	int		i;
	char	*tmp;

	if (!line || !ft_isprint(line[0]))
		return ;
	if (g_h->curr < HISTFILESIZE)
	{
		free(g_h->hist[g_h->curr]);
		g_h->hist[g_h->curr++] = ft_strdup(line);
		g_h->hist[g_h->curr] = ft_strnew(0);
	}
	else
	{
		i = 0;
		while (i < g_h->curr - 1)
		{
			tmp = g_h->hist[i];
			g_h->hist[i] = ft_strdup(g_h->hist[i + 1]);
			free(tmp);
			i++;
		}
		tmp = g_h->hist[i];
		g_h->hist[i] = ft_strdup(line);
		free(tmp);
	}
	g_h->hst = g_h->curr;
}

char		*ft_process_history(t_l *l)
{
	
	if (l->line)
	{
		if (ft_hist_exp(l))
			ft_printf("\n%s", l->line);
	}
	if (!ft_check_cont(l->line))
		append_history(l->line);
	return (l->line);
}

void		delete_save_history(void)
{
	int		i;
	int		fd;
	
	if (g_h->curr == 0)
		return ;
	fd = open("./.history", O_TRUNC | O_WRONLY);
	i = -1;
	while (++i < g_h->curr)
	{
		write(fd, g_h->hist[i], ft_strlen(g_h->hist[i]));
		if (i + 1 < g_h->curr)
			write(fd, "\n", 1);
	}
	close(fd);
}
