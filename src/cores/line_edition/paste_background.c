/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paste_background.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihwang <ihwang@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/21 03:36:24 by marvin            #+#    #+#             */
/*   Updated: 2021/03/13 20:25:26 by ihwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static void	shorten_spaces(char *clip)
{
	while (*clip)
	{
		if (*clip == '\n' || *clip == '\t')
			*clip = ' ';
		++clip;
	}
}

static char	*get_initial_clip(char raw_clip[])
{
	char	*clip;

	if (ft_strlen(raw_clip) >= BUFF_LINE_EDITION)
		clip = ft_strndup(raw_clip, BUFF_LINE_EDITION);
	else
		clip = ft_strdup(raw_clip);
	return (clip);
}

char		*get_clip_external(char raw_clip[])
{
	char			*clip;
	char			*temp;
	char			buf[BUFF_LINE_EDITION];
	int				buflen;
	t_term			raw;

	clip = get_initial_clip(raw_clip);
	temp = NULL;
	tcgetattr(0, &raw);
	raw.c_cc[VMIN] = 0;
	raw.c_cc[VTIME] = 0;
	tcsetattr(0, TCSANOW, &raw);
	while ((buflen = read(STDIN_FILENO, buf, BUFF_LINE_EDITION)) > 0)
	{
		temp = ft_strnjoin(clip, buf, buflen);
		ft_strdel(&clip);
		clip = temp;
	}
	raw.c_cc[VMIN] = 1;
	raw.c_cc[VTIME] = 0;
	tcsetattr(0, TCSANOW, &raw);
	shorten_spaces(clip);
	return (clip);
}

void		paste_background(t_l *l, int clip_len)
{
	l->y += (l->x + clip_len) / l->co;
	l->x = (l->x + clip_len) % l->co;
	if (l->x == 0)
		tputs(tgoto(tgetstr("cm", NULL), 0, \
				get_current_row() - 1), 1, ft_putchar);
	l->nb += clip_len;
}
