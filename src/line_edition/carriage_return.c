/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   carriage_return.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihwang <ihwang@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/02 15:29:56 by tango             #+#    #+#             */
/*   Updated: 2020/10/01 14:41:59 by ihwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	carriage_return_key(t_l *l, t_h **h)
{
	append_history(l, h);
	up_down(l, h, NULL);
	restore_term(l);
	auto_reset(&l->auto_com);
}
