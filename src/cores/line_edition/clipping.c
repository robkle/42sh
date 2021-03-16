/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clipping.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihwang <ihwang@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/20 00:20:27 by ihwang            #+#    #+#             */
/*   Updated: 2021/03/13 20:54:42 by ihwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

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
