/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eof_handler.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthan <dthan@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/02 16:09:25 by tango             #+#    #+#             */
/*   Updated: 2021/01/05 15:59:16 by dthan            ###   ########.fr       */
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

/* no need, eof is not signal
void		eof_handler(t_l *l)
{
	char	*tmp;
	t_term	old;

	if (l->phase == EDTR_PHASE_DFLT)
	{
		restore_term(l);
		ft_exit(EXIT_SUCCESS);
	}
	else if (l->phase == EDTR_PHASE_DQUOT)
	{
		ft_dprintf(2, "\n%s: unexpected EOF while looking for matching `\"\'\n", SHELL_NAME);
		tmp = ft_strjoin(l->line, "\"");
		ft_strdel(&l->line);
		l->line = tmp;
	}
	old = get_set_default_term(NULL);
	tcsetattr(0, TCSANOW, &old);
}

char *eof_handler(t_l *l, t_editor_phase *phase)
{
	//restore term
	if (*phase == EDTR_PHASE_DFLT)
		ft_exit(EXIT_SUCCESS);
	else if (*phase == EDTR_PHASE_DQUOTE || *phase == EDTR_PHASE_QUOTE || *phase == EDTR_PHASE_BACKSLASH)
	{
		if (*phase == EDTR_PHASE_DQUOTE || *phase == EDTR_PHASE_QUOTE)
		{
			ft_dprintf(2, "%s: unexpected EOF while looking for matching `%c\'\n", SHELL_NAME, (*phase == EDTR_PHASE_DQUOTE) ? '\"' : '\'');
			ft_dprintf(2, "%s: syntax error: unexpected end of file\n", SHELL_NAME);
		}
		return (NULL);
	}
	return l->line;
}
*/