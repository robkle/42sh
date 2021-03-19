/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   carriage_return.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthan <dthan@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/02 15:29:56 by tango             #+#    #+#             */
/*   Updated: 2021/03/19 21:57:52 by rklein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void		carriage_return_key(t_l *l)
{
	if (l->rs)
		ft_reverse_search_reset(l);
	if (l->line == NULL)
		l->line = ft_strnew(2);
	l->line = ft_strjoin_and_free_string1(l->line, "\n");
	up_down(l, NULL);
}
