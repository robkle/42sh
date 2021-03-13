/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_key.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihwang <ihwang@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/03 11:41:34 by rklein            #+#    #+#             */
/*   Updated: 2021/03/13 21:18:47 by ihwang           ###   ########.fr       */
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
		return (paste(line_edition, buf, NULL));
	return (EXIT_SUCCESS);
}

int		parse_line_edition_key(char buf[BUFF_LINE_EDITION], t_l *line_edition)
{
	if (ft_strequ(buf, BACKSLASH_KEY))
		return (bs_key(line_edition));
	else if (ft_strequ(buf, CUT_KEY))
		return (cutting(line_edition, 0));
	else if (ft_strequ(buf, PASTE_KEY))
		return (paste(line_edition, NULL, NULL));
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
