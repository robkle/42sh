/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_line.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihwang <ihwang@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/29 19:13:18 by ihwang            #+#    #+#             */
/*   Updated: 2021/03/18 19:47:11 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

/*
** parse_key
**	@buf			: the buffer from read()
**	@line_edition	: line_edition struct
**	@phase			: the editting phase
** function parse key will parse every available key and return according to
** the status of each key's execution. If there is no available key, then
** this function will return SUCCESS so that the loop can keep looping
** In general, I divide into 4 main categories
**		1. Signal key, every key related to signal will go here
**			Right now, there is only SIGINT, if there are more, add here
**		2. Line editing key, key related to manipulate the string like
**			deleting(backslash + delete key), cutting and pasting, arrow keys
**			and moving cursor like home and end key
**		3. The feature of editing will go here, right now we have auto-
**			completion and history search, if more feature, it will go to here
**		4. Normal key stroke will go be added in the line
**	Posibility of the return of each category:
**		1. Signal -> Always return EXIT FAILURE
**		2. Line editing key -> Always return EXIT SUCCESS, seems like no need
**			for return EXIT FAILURE here
**		3. Feature -> return EXIT SUCCESS or EXIT FAILURE, SUCCESS when the
**			feature is not interfered by the signal, for example SIGINT
**			. FAILURE when there is something wrong happened when the feature
**			is running
**		4. Normal key stroke -> Always return EXIT SUCCESS
*/

int			parse_key(char buf[BUFF_LINE_EDITION], t_l *line_edition)
{
	if (is_line_edition_key(buf))
		return (parse_line_edition_key(buf, line_edition));
	else if (is_feature_key(buf))
		return (parse_feature_key(buf, line_edition));
	else if (buf[0] && buf[1] == '\0' && ft_isprint(buf[0]))
		return (add_key(buf, line_edition));
	return (EXIT_SUCCESS);
}

void		init_line_edition(t_l *line_edition, t_prompt prompt_type)
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
	line_edition->lc = NULL;//NEW
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

void		prepare_breaking_loop(
	char buf[BUFF_LINE_EDITION], t_l *line_edition, t_phase *phase,
	t_lex_value lex_value)
{
	if (ft_strequ(buf, ENTER_KEY))
		line_edition->line = ft_strjoin_and_free_string1(
			line_edition->line, "\n");
	else if (ft_strequ(buf, CTRL_D_KEY))
	{
		if (*phase == PHASE_CMD && lex_value == LEX_CMD)
		{
			restore_term(line_edition);
			ft_exit_internal(g_shell.exit_status);
		}
		line_edition->line = ft_strjoin_and_free_string1(
			line_edition->line, "\x04");
		*phase = PHASE_STOP;
	}
}

void prepare_breaking_loop_due_to_signal(t_l *line_edition, int reverse_search_reset)
{
	if (reverse_search_reset)
	{
		if (line_edition->rs)
			ft_reverse_search_reset(line_edition);
		
	}
	(line_edition->line) ? free(line_edition->line) : 0;
	line_edition->line = NULL;
}

static void	ft_read_input(t_get_line_service *self, t_phase *phase, t_lex_value lex_value)
{
	while (read(STDIN_FILENO, self->buf, BUFF_LINE_EDITION) != -1)
	{
		if (g_shell.signal_indicator == SIGWINCH)
			handle_sigwinch(&(self->line_edition));
		ft_line_count(&(self->line_edition));//NEW
		if (g_shell.signal_indicator == SIGINT)
		{
			prepare_breaking_loop_due_to_signal(&(self->line_edition), 1);
			break ;
		}
		if (self->line_edition.rs && (ft_strequ(self->buf, ENTER_KEY) || \
		ft_strequ(self->buf, CTRL_D_KEY)))
			ft_reverse_search_reset(&(self->line_edition));
		if (ft_strequ(self->buf, ENTER_KEY) || \
		(ft_strequ(self->buf, CTRL_D_KEY) && self->line_edition.nb == 0))
		{
			prepare_breaking_loop(self->buf, &(self->line_edition), phase, lex_value);
			break ;
		}
		else if (parse_key(self->buf, &(self->line_edition)) == EXIT_FAILURE)
		{
			prepare_breaking_loop_due_to_signal(&(self->line_edition), 0);
			break ;
		}
		ft_bzero(self->buf, BUFF_LINE_EDITION);
	}
}

// char		*ft_get_line(
// 	t_phase *phase, t_prompt prompt_type, t_lex_value lex_value)
// {
// 	t_l		line_edition;

// 	print_prompt(prompt_type);
// 	init_term();
// 	init_line_edition(&line_edition, prompt_type);
// 	ft_read_input(&line_edition, phase, lex_value);
// 	restore_term(&line_edition);
// 	return (line_edition.line);
// }

void init_get_line_service(t_get_line_service *self, t_prompt prompt_type)
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
	ft_arraydel(instance.line_edition.lc);//NEW
	ft_strdel(&instance.line_edition.current);//NEW
	return (instance.line_edition.line);
}
