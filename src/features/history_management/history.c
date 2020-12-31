/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthan <dthan@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/20 00:22:24 by ihwang            #+#    #+#             */
/*   Updated: 2020/12/26 13:47:05 by dthan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void		get_history(int fd)
{
	char	*line;
	char	buffer[4096];
	int		i;

	fd = open(g_shell.history->savedfile, O_RDWR | O_CREAT, 0644);
	ft_bzero(buffer, 4096);
	i = 0;
	while (get_next_line(fd, &line) && i <= HISTFILESIZE)	
	{
		ft_strcat(buffer, line);
		if (!ft_check_cont(buffer))
		{
			g_shell.history->hist[i++] = ft_strdup(buffer);
			g_shell.history->curr = i;
			ft_bzero(buffer, ft_strlen(buffer));
		}
		else
			ft_strcat(buffer, "\n");
		free(line);
	}
	g_shell.history->hst = g_shell.history->curr;
	g_shell.history->hist[i++] = ft_strnew(0);
	g_shell.history->hist[i] = NULL;
	g_shell.history->hstsize = HISTFILESIZE;
	close(fd);
}

static void append_history_realloc(void)
{
	char **tmp;
	int i;

	g_shell.history->hstsize += HISTFILESIZE;
	tmp = (char**)ft_memalloc(sizeof(char*) * (g_shell.history->hstsize + 2));
	i = -1;
	while (++i < g_shell.history->curr)
		tmp[i] = ft_strdup(g_shell.history->hist[i]);
	tmp[i++] = ft_strdup(g_shell.history->tmp);
	g_shell.history->curr = i;
	tmp[i++] = ft_strnew(0);
	tmp[i] = NULL;
	ft_arraydel(g_shell.history->hist);
	g_shell.history->hist = tmp;
}

void		append_history(void)
{
	if (!g_shell.history->tmp || !ft_isprint(g_shell.history->tmp[0]))
		return ;
	if (g_shell.history->curr < g_shell.history->hstsize)
	{
		free(g_shell.history->hist[g_shell.history->curr]);
		g_shell.history->hist[g_shell.history->curr++] = ft_strdup(g_shell.history->tmp);
		g_shell.history->hist[g_shell.history->curr] = ft_strnew(0);
		g_shell.history->hist[g_shell.history->curr + 1] = NULL;
	}
	else
		append_history_realloc();
	g_shell.history->hst = g_shell.history->curr;
	free(g_shell.history->tmp);
	g_shell.history->tmp = NULL;
}

char		*ft_process_history(t_l *l)
{
	if (l->line)
	{
		if (ft_hist_exp(l))
			ft_printf("%s", l->line);
	}
	if (!ft_check_cont(l->line))
	{
		if (g_shell.history->tmp)
			free(g_shell.history->tmp);
		g_shell.history->tmp = ft_strsub(l->line, 0, ft_strlen(l->line) - 1);
	}
	return (l->line);
}

void		delete_save_history(void)
{
	int		i;
	int		fd;
	
	if (g_shell.history->curr == 0)
		return ;
	fd = open(g_shell.history->savedfile, O_TRUNC | O_WRONLY | O_CREAT);
	i = (g_shell.history->curr > HISTFILESIZE) ? g_shell.history->curr - HISTFILESIZE - 1 : -1;
	while (++i < g_shell.history->curr)
	{
		ft_dprintf(fd, "%s", g_shell.history->hist[i]);
		if (i + 1 < g_shell.history->curr)
			write(fd, "\n", 1);
	}
	close(fd);
}
