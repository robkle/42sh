/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_line.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihwang <ihwang@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/29 19:13:18 by ihwang            #+#    #+#             */
/*   Updated: 2021/03/19 23:16:41 by rklein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	init_line_edition(t_l *line_edition, t_prompt prompt_type)
{
	tgetent(NULL, ft_getenv("TERM"));
	ft_bzero(line_edition, sizeof(t_l));
	line_edition->line = ft_strnew(0);
	line_edition->nb = 0;
	line_edition->co = tgetnum("co");
	line_edition->total_row = tgetnum("li");
	line_edition->starting_row = line_edition->total_row - get_current_row();
	line_edition->pmpt = prompt_len(prompt_type);
	line_edition->x = line_edition->pmpt;
	line_edition->y = 0;
	line_edition->promp_type = prompt_type;
	line_edition->rs = 0;
	line_edition->lc = NULL;
}

/*
** ft_get_line
**	@phase: the phase of editing, could be default, quote or dquote...
** The function ft_get_line will be used to take a single line input from the
** user
** STEP:
**	1. Initializing struct line edition
**	2. Make terminal into cooked / raw mode
**	3. Looping every key stroke from user through buffer
**		Cases make loop stop:
**		a, When user hit enter or the line is empty and user hit ctrl-d (ctrl-d
**		is not a signal, it is end of file character)
**		b. When the return from parse_key function is EXIT_FAILURE
**	4. When the loop is break, we restore the terminal
**	RETURN VALUE:
**		There are 3 possible of returning value here:
**			+ NULL : when there is something wrong happens
**			+ A string: A string with a '\n' or '\x04' at the end of the line
**			+ A string with the length == 0
**		So far, I couldnt find a case to return a string with the length == 0
**		yet, but it could be useful in the future
*/

void	init_get_line_service(t_get_line_service *self, t_prompt prompt_type)
{
	print_prompt(prompt_type);
	ft_bzero(self->buf, BUFF_LINE_EDITION);
	init_term();
	init_line_edition(&(self->line_edition), prompt_type);
}

char	*ft_get_line(
	t_phase *phase, t_prompt prompt_type, t_lex_value lex_value)
{
	t_get_line_service instance;

	print_prompt(prompt_type);
	ft_bzero(instance.buf, BUFF_LINE_EDITION);
	init_term();
	init_line_edition(&(instance.line_edition), prompt_type);
	ft_read_input(&instance, phase, lex_value);
	restore_term(&(instance.line_edition));
	ft_arraydel(instance.line_edition.lc);
	ft_strdel(&instance.line_edition.current);
	return (instance.line_edition.line);
}
