/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthan <dthan@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/20 00:22:24 by ihwang            #+#    #+#             */
/*   Updated: 2021/03/18 09:44:29 by rklein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void		get_history(int fd)
{
	char	*line;
	char	buffer[4096];
	char	buffer_history_with_line_break[4096];
	int		i;
	int		end_pos;
	int j= 1;

	fd = open(g_shell.history->savedfile, O_RDWR | O_CREAT, 0644);
	ft_bzero(buffer, 4096);
	i = 0;
	while (get_next_line(fd, &line) && i <= HISTFILESIZE)
	{	
		ft_strcat(buffer, line);
		if ((end_pos = ft_check_continue_hist(buffer)) != -1)
		{
			// ft_printf("before buffer: %s\n", buffer);
			ft_bzero(buffer_history_with_line_break, 4096);
			ft_strcpy(buffer_history_with_line_break, buffer);
			ft_strcat(buffer_history_with_line_break, "\n");
			g_shell.history->hist[i++] = ft_strdup(buffer_history_with_line_break);
			g_shell.history->curr = i;
			// ft_printf("%d\n", end_pos);
			// ft_printf("when the left over: [%s]\n", &buffer[end_pos]);
			ft_strcpy(buffer, &buffer[end_pos]);
			// ft_printf("after buffer: %s\n", buffer);
			j++;
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

/*void		get_history(int fd)
{
	char	*line;
	char	buffer[4096];
	int		i;
	int j = 1;

	fd = open(g_shell.history->savedfile, O_RDWR | O_CREAT, 0644);
	ft_bzero(buffer, 4096);
	i = 0;
	while (get_next_line(fd, &line) && i <= HISTFILESIZE)
	{
		ft_printf("%d\n", j++);
		ft_strcat(buffer, line);
		if (!ft_check_cont(buffer))
		{
			ft_printf("%s\n", buffer);
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
}*/

static void	append_history_realloc(void)
{
	char	**tmp;
	int		i;

	g_shell.history->hstsize += HISTFILESIZE;
	tmp = (char**)ft_memalloc(sizeof(char*) * (g_shell.history->hstsize + 2));
	i = -1;
	while (++i < g_shell.history->curr)
		tmp[i] = g_shell.history->hist[i];
	tmp[i] = ft_strdup(g_shell.history->tmp);
	g_shell.history->curr = i;
	tmp[i++] = ft_strnew(0);
	tmp[i] = NULL;
	free(g_shell.history->hist);
	g_shell.history->hist = tmp;
}

/*
**
`echo abc"\n
\n
\n
\"\n\0`
-->
"echo abc


"     (note the line break after the closing dquote is the enter)
-->
what need to do in the history here:
when user press up or down -> we bring to the user to see this format of the history
`echo abc"\n
\n
\n
\"\0    -->(we dont bring up the enter character anymore)
`
if they start edding the history line -> we copy this history line to line_edition_line
`echo abc"\n
\n
\n
\"\0`
------------
case 2
`echo abc"\n
\n
\n
^D\0`
-->
"echo abc"


<hidden_ctrol-d>
what need to do in the history here:
when user press up or down -> we bring to the user to see this format of the history
`echo abc"\n
\n
\n
\0`
if they start edding the history line -> we copy this history line to line_edition_line
`echo abc"\n
\n
\n
\0`
*/

void		append_history(void)
{
	if (g_shell.history->curr < g_shell.history->hstsize)
	{
		// before, you deleted the \n ^D
		free(g_shell.history->hist[g_shell.history->curr]);
		g_shell.history->hist[g_shell.history->curr++] = ft_strdup(g_shell.history->tmp);
		g_shell.history->hist[g_shell.history->curr] = ft_strnew(0);
		g_shell.history->hist[g_shell.history->curr + 1] = NULL;
	}
	else
		append_history_realloc();
	g_shell.history->hst = g_shell.history->curr;
	g_shell.history->tmp = NULL;
}

void		delete_save_history(void)
{
	int		i;
	int		fd;

	if (g_shell.history->curr == 0)
		return ;
	fd = open(g_shell.history->savedfile, O_TRUNC | O_WRONLY | O_CREAT);
	i = (g_shell.history->curr > HISTFILESIZE) ? \
	g_shell.history->curr - HISTFILESIZE - 1 : -1;
	while (++i < g_shell.history->curr)
		ft_dprintf(fd, "%s", g_shell.history->hist[i]);
	close(fd);
}
