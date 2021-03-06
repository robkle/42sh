/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   analyzing_phase.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthan <dthan@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/06 20:07:37 by dthan             #+#    #+#             */
/*   Updated: 2021/03/07 01:36:30 by dthan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	analyzing_phase_inhibitor(t_phase phase[], int *stack_pos, char ch)
{
	if (ch == '"')
	{
		if (!is_quoting_phase(phase[(*stack_pos)]))
			phase[++(*stack_pos)] = PHASE_DQUOTE;
		else if (phase[*stack_pos] == PHASE_DQUOTE)
			phase[(*stack_pos)--] = 0;
	}
	else if (ch == '\'')
	{
		if (!is_quoting_phase(phase[(*stack_pos)]))
			phase[++(*stack_pos)] = PHASE_QUOTE;
		else if (phase[*stack_pos] == PHASE_QUOTE)
			phase[(*stack_pos)--] = 0;
	}
	else if (ch == '\\')
	{
		if (!is_quoting_phase(phase[(*stack_pos)]))
			phase[++(*stack_pos)] = PHASE_BACKSLASH;
	}
}

void	analyzing_phase_open_expansion(t_phase phase[], int *stack_pos, char ch)
{
	if (ch == '{')
		phase[++(*stack_pos)] = PHASE_BRACEPARAM;
	else if (ch == '(')
		phase[++(*stack_pos)] = PHASE_CMDSUBST;
}

void	analyzing_phase_close_expansion(
	t_phase phase[], int *stack_pos, char ch)
{
	if (ch == '}')
	{
		if (phase[*stack_pos] == PHASE_BRACEPARAM)
			phase[(*stack_pos)--] = 0;
	}
	else if (ch == ')')
	{
		if (phase[*stack_pos] == PHASE_CMDSUBST)
			phase[(*stack_pos)--] = 0;
	}
}

/*
** need to check again the len
*/

void	analyzing_phase(char *str, t_phase phase[], int *stack_pos)
{
	int i;
	int len;

	i = -1;
	len = ft_strlen(str) - 1;
	while (++i < len)
	{
		if (phase[*stack_pos] == PHASE_BACKSLASH)
		{
			phase[(*stack_pos)--] = 0;
			continue;
		}
		if (str[i] == '"' || str[i] == '\'' || str[i] == '\\')
			analyzing_phase_inhibitor(phase, stack_pos, str[i]);
		else if (is_open_curly_bracket_for_parameter_expansion(
				str, i, phase, *stack_pos) ||
			is_open_parenthesis_for_arthimetic_expansion(
				str, i, phase, *stack_pos))
			analyzing_phase_open_expansion(phase, stack_pos, str[i]);
		else if ((str[i] == '}' || str[i] == ')') && is_real_character(str, i))
			analyzing_phase_close_expansion(phase, stack_pos, str[i]);
	}
}
