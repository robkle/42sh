/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clipping.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihwang <ihwang@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/20 00:20:27 by ihwang            #+#    #+#             */
/*   Updated: 2020/10/03 17:00:40 by ihwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "copy_paste.h"

char				*clipboard(char *str, int opt)
{
	static char		*clip;

	if (opt == CLIP_SAVE)
	{
		if (clip)
			ft_strdel(&clip);
		clip = ft_strdup(str);
	}
	else if (opt == CLIP_TAKE)
	{
		if (clip)
			return (clip);
	}
	else
		ft_strdel(&clip);
	return (NULL);
}

void				cutting_clipping(t_l *l, int i, int j)
{
	char			*clip;

	clip = ft_strnew(j - i);
	clip = ft_strncpy(clip, &l->line[i], j - i);
	clipboard(clip, CLIP_SAVE);
	ft_strdel(&clip);
}
