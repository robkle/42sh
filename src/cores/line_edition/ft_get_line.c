/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_line.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthan <dthan@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/29 19:13:18 by ihwang            #+#    #+#             */
/*   Updated: 2021/01/28 14:29:49 by dthan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

/*
** line edition key
*/

int		is_line_edition_key(char buf[BUFF_LINE_EDITION])
{
	if (ft_strequ(buf, BACKSLASH_KEY) || ft_strequ(buf, CUT_KEY) ||
		ft_strequ(buf, HOME_KEY) || ft_strequ(buf, END_KEY) ||
		ft_strequ(buf, PASTE_KEY) || ft_strequ(buf, UP_ARROW_KEY) ||
		ft_strequ(buf, DOWN_ARROW_KEY) || ft_strequ(buf, LEFT_ARROW_KEY) ||
		ft_strequ(buf, RIGHT_ARROW_KEY) || ft_strequ(buf, CTRL_UP_KEY) ||
		ft_strequ(buf, CTRL_DOWN_KEY) || ft_strequ(buf, CTRL_RIGHT_KEY) ||
		ft_strequ(buf, CTRL_LEFT_KEY) || ft_strequ(buf, ESC_KEY) ||
		(ft_strlen(buf) > 1 && ft_isprint(buf[0])))
		return (1);
	return (0);
}

int		parse_line_edition_key2(char buf[BUFF_LINE_EDITION], t_l *line_edition)
{
	if (ft_strequ(buf, UP_ARROW_KEY) || ft_strequ(buf, DOWN_ARROW_KEY))
		return (up_down(line_edition, buf));
	else if (ft_strequ(buf, RIGHT_ARROW_KEY))
		return (right_key(line_edition));
	else if (ft_strequ(buf, LEFT_ARROW_KEY))
		return (left_key(line_edition));
	else if (ft_strequ(buf, CTRL_UP_KEY))
		return (ctrl_up(line_edition));
	else if (ft_strequ(buf, CTRL_DOWN_KEY))
		return (ctrl_down(line_edition));
	else if (ft_strequ(buf, CTRL_RIGHT_KEY))
		return (ctrl_right(line_edition));
	else if (ft_strequ(buf, CTRL_LEFT_KEY))
		return (ctrl_left(line_edition, 0));
	else if (ft_strequ(buf, ESC_KEY) && line_edition->rs)
		return (ft_reverse_search_reset(line_edition));
	else if (ft_strlen(buf) > 1 && ft_isprint(buf[0]))
		return (paste(line_edition, buf, 0, NULL));
	return (EXIT_SUCCESS);
}

int		parse_line_edition_key(char buf[BUFF_LINE_EDITION], t_l *line_edition)
{
	if (ft_strequ(buf, BACKSLASH_KEY))
		return (bs_key(line_edition));
	else if (ft_strequ(buf, CUT_KEY))
		return (cutting(line_edition, 0));
	else if (ft_strequ(buf, PASTE_KEY))
		return (paste(line_edition, NULL, 0, NULL));
	else if (ft_strequ(buf, HOME_KEY))
		return (home_key(line_edition));
	else if (ft_strequ(buf, END_KEY))
		return (end_key(line_edition));
	return (parse_line_edition_key2(buf, line_edition));
}

/*
** feature key
*/

int		is_feature_key(char buf[BUFF_LINE_EDITION])
{
	if (ft_strequ(buf, TAB_KEY))
		return (1);
	else if (ft_strequ(buf, CTRL_R_KEY))
		return (1);
	return (0);
}

int		parse_feature_key(char buf[BUFF_LINE_EDITION], t_l *line_edition)
{
	if (ft_strequ(buf, TAB_KEY))
		return (auto_complete(line_edition));
	else if (ft_strequ(buf, CTRL_R_KEY))
		return (ft_reverse_search(line_edition));
	return (EXIT_FAILURE);
}

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

int		parse_key(char buf[BUFF_LINE_EDITION], t_l *line_edition)
{
	if (is_line_edition_key(buf))
		return (parse_line_edition_key(buf, line_edition));
	else if (is_feature_key(buf))
		return (parse_feature_key(buf, line_edition));
	else if (buf[0] && buf[1] == '\0' && ft_isprint(buf[0]))
		return (add_key(buf, line_edition));
	return (EXIT_SUCCESS);
}

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

void	prepare_breaking_loop(
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
			ft_exit(EXIT_SUCCESS);
		}
		line_edition->line = ft_strjoin_and_free_string1(
			line_edition->line, "\x04");
		*phase = PHASE_STOP;
	}
}

char	*ft_get_line(
	t_phase *phase, t_prompt prompt_type, t_lex_value lex_value)
{
	t_l		line_edition;
	char	buf[BUFF_LINE_EDITION];
	char	*ret;

	print_prompt(prompt_type);
	ft_bzero(buf, sizeof(buf));
	init_term();
	init_line_edition(&line_edition, prompt_type);
	while (read(STDIN_FILENO, buf, sizeof(buf)) != -1)
	{
		if (g_shell.signal_indicator == SIGINT)
		{
			if (line_edition.rs)
				ft_reverse_search_reset(&line_edition);
			free(line_edition.line);
			line_edition.line = NULL;
			break ;
		}
		if (line_edition.rs && (ft_strequ(buf, ENTER_KEY) ||
			ft_strequ(buf, CTRL_D_KEY)))
			ft_reverse_search_reset(&line_edition);
		if (ft_strequ(buf, ENTER_KEY) ||
			(ft_strequ(buf, CTRL_D_KEY) && line_edition.nb == 0))
		{
			prepare_breaking_loop(buf, &line_edition, phase, lex_value);
			break ;
		}
		else if (parse_key(buf, &line_edition) == EXIT_FAILURE)
		{
			free(line_edition.line);
			line_edition.line = NULL;
			break ;
		}
		ft_bzero(buf, sizeof(buf));
	}
	restore_term(&line_edition);
	ret = line_edition.line;
	return (ret);
}
