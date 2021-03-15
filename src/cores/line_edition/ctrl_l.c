/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ctrl_l.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthan <dthan@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/05 01:37:15 by tango             #+#    #+#             */
/*   Updated: 2021/03/15 16:39:41 by rklein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static void	paste_apply_screen(t_l *l, char *clip, int i)
{
	apply_termcap_str("cd", 0, 0);
	ft_putstr(clip);
	apply_termcap_str("sc", 0, 0);
	if (l->line)
		ft_putstr(&l->line[i]);
	apply_termcap_str("rc", 0, 0);
}

static void	wind_up_cursor(t_l *l/*, int clip_len*/)
{
	int				starting_row_from_top;
	int				row_position;
	int				nb_rewind;
	int				gap_between_begin_end;

	//l->starting_row = (l->nb + clip_len + l->pmpt) / l->co;//OLD
	l->starting_row = ft_row_count(l) - 1;//NEW
	starting_row_from_top = l->total_row - l->starting_row;
	//gap_between_begin_end = (l->y * l->co + l->x + clip_len) / l->co;//OLD
	gap_between_begin_end = ft_y_pos(l, ft_index_calc(l)); //NEW
	row_position = starting_row_from_top + gap_between_begin_end;
	nb_rewind = get_current_row() - row_position;
	while (nb_rewind-- > 0)
	{
		apply_termcap_str("up", 0, 0);
	}
}

int			paste(t_l *l, char raw_clip[], int clip_len, char *autocom_clip)
{
	char			*clip;
	char			*tmp;
	int				i;

	if (autocom_clip)
		clip = autocom_clip;
	else if (raw_clip)
		clip = get_clip_external(raw_clip);
	else if (!(clip = clipboard(NULL, CLIP_TAKE)))
		return (EXIT_SUCCESS);
	clip_len = ft_strlen(clip);
	//i = l->x + (l->y * l->co) - l->pmpt;//OLD
	i = ft_index_calc(l);//NEW
	paste_apply_screen(l, clip, i);
	tmp = ft_strnew(l->nb + clip_len);
	if (l->line)
		tmp = ft_strncpy(tmp, l->line, i);
	tmp = ft_strcat(tmp, clip);
	if (l->line)
		tmp = ft_strcat(tmp, &l->line[i]);
	ft_strdel(&l->line);
	l->line = tmp;
	//if (l->starting_row < (l->nb + l->pmpt + clip_len) / l->co)//OLD
	if (l->starting_row < ft_row_count(l) - 1)//NEW
		wind_up_cursor(l/*, clip_len*/);
	paste_background(l, clip_len);
	return (EXIT_SUCCESS);
}
