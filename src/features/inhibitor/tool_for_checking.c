/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tool_for_checking.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthan <dthan@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/04 06:21:11 by dthan             #+#    #+#             */
/*   Updated: 2021/03/12 22:44:26 by dthan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int	is_quoting_phase(t_phase cur_phase)
{
	if (cur_phase == PHASE_QUOTE ||
		cur_phase == PHASE_DQUOTE ||
		cur_phase == PHASE_BACKSLASH)
		return (1);
	return (0);
}

int	is_real_character(char *str, int i)
{
	int ct;

	if (i == 0)
		return (1);
	ct = 0;
	while (i-- >= 0 && str[i] == '\\')
		ct++;
	if (ct % 2 == 0)
		return (1);
	return (0);
}
