/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   analyzing_phase_helper.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthan <dthan@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/06 20:09:44 by dthan             #+#    #+#             */
/*   Updated: 2021/03/07 01:34:46 by dthan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int	is_open_curly_bracket_for_parameter_expansion(
	char *str, int i, t_phase phase[], int stack_pos)
{
	if (str[i] == '{' &&
		((phase[stack_pos] == PHASE_CMD &&
			i > 0 && str[i - 1] == '$' &&
			is_real_character(str, i - 1))
		|| (phase[stack_pos] == PHASE_BRACEPARAM &&
			is_real_character(str, i))))
		return (1);
	return (0);
}

int	is_open_parenthesis_for_arthimetic_expansion(
	char *str, int i, t_phase phase[], int stack_pos)
{
	if (str[i] == '(' &&
	((phase[stack_pos] == PHASE_CMD &&
		i > 0 && str[i - 1] == '$' &&
		is_real_character(str, i - 1))
	|| (phase[stack_pos] == PHASE_CMDSUBST &&
		is_real_character(str, i))))
		return (1);
	return (0);
}
