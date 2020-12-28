/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eof_handler.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthan <dthan@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/02 16:09:25 by tango             #+#    #+#             */
/*   Updated: 2020/12/14 12:50:26 by dthan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int			iseof_in_line(char *line)
{
	while (*line)
	{
		if (*line == '\x04')
			return (1);
		++line;
	}
	return (0);
}

void		eof_handler(t_l *l)
{
	char	*tmp;
	t_term	old;

	if (l->type == LINE_TYPE_SINGLE)
	{
		restore_term(l);
		ft_exit(EXIT_SUCCESS);
	}
	else if (l->type == LINE_TYPE_DQUOTE)
	{
		ft_dprintf(2, "\n%s: unexpected EOF while looking for matching `\"\'\n", SHELL_NAME);
		tmp = ft_strjoin(l->line, "\"");
		ft_strdel(&l->line);
		l->line = tmp;
	}
	old = get_set_default_term(NULL);
	tcsetattr(0, TCSANOW, &old);
}
