/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   carriage_return.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthan <dthan@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/02 15:29:56 by tango             #+#    #+#             */
/*   Updated: 2020/12/26 19:21:53 by dthan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	carriage_return_key(t_l *l)
{
/*	if (l->line)
	{
		if (ft_hist_exp(l))
			ft_printf("\n%s", l->line);
	}
	append_history(l);*/
	if (l->rs)
		ft_reverse_search_reset(l);
	up_down(l, NULL);
	restore_term(l);
	auto_reset(&l->auto_com);
}
