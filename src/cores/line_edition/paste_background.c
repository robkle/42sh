/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paste_background.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthan <dthan@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/21 03:36:24 by marvin            #+#    #+#             */
/*   Updated: 2020/12/27 18:03:32 by dthan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static void			unify_space(char *clip)
{
	while (*clip)
	{
		if (*clip == '\n' || *clip == '\t')		
			*clip = ' ';
		++clip;
	}
}

char				*get_clip_external(char raw_clip[])
{
	char			*clip;
	char			*temp;
	char			buf[BUFF_LINE_EDITION];
	int				len;

	if (ft_strlen(raw_clip) >= BUFF_LINE_EDITION)
		clip = ft_strndup(raw_clip, BUFF_LINE_EDITION);
	else
		clip = ft_strdup(raw_clip);
	temp = NULL;
	while (read(STDIN_FILENO, buf, BUFF_LINE_EDITION) > 0)
	{
		temp == NULL ? ioctl(0, TIOCSTI, "") : 0;
		temp = ft_strnjoin(clip, buf, BUFF_LINE_EDITION, &len);
		ft_strdel(&clip);
		clip = temp;
		if (len != BUFF_LINE_EDITION)
			break ;
	}
	unify_space(clip);
	return (clip);
}

void				paste_background(t_l *l, int clip_len)
{
	l->y += (l->x + clip_len) / l->co;
	l->x = (l->x + clip_len) % l->co;
	if (l->x == 0)
		tputs(tgoto(tgetstr("cm", NULL), 0, \
				get_current_row() - 1), 1, ft_putchar);
	l->nb += clip_len;
}
