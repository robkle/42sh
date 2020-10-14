/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   carriage_return.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tango <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/02 15:29:56 by tango             #+#    #+#             */
/*   Updated: 2020/08/05 05:42:43 by tango            ###   ########.fr       */
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
	up_down(l, NULL);
	restore_term(l);
}
