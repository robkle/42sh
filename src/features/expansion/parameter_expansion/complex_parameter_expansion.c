/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   complex_parameter_expansion.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthan <dthan@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/27 11:05:46 by dthan             #+#    #+#             */
/*   Updated: 2021/02/28 13:55:20 by dthan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int	parameter_expansion_colon_minus_case(t_parameter_expansion *self,
	t_parameter_expansion_type type)
{
	if (type == PE_SET_AND_NOT_NULL)
		substitute_parameter(self->parameter, self->replacement);
	else if (type == PE_SET_BUT_NULL || type == PE_UNSET)
		substitute_word(self->word, self->replacement);
	return (EXIT_SUCCESS);
}

int	parameter_expansion_colon_equal_case(t_parameter_expansion *self,
	t_parameter_expansion_type type)
{
	if (type == PE_SET_AND_NOT_NULL)
		substitute_parameter(self->parameter, self->replacement);
	else if (type == PE_SET_BUT_NULL || type == PE_UNSET)
	{
		assign_word(self->parameter, self->word);
		ft_strcpy(self->replacement, self->word);
	}
	return (EXIT_SUCCESS);
}

int	parameter_expansion_colon_question_case(t_parameter_expansion *self,
	t_parameter_expansion_type type)
{
	if (type == PE_SET_AND_NOT_NULL)
		substitute_parameter(self->parameter, self->replacement);
	else if (type == PE_SET_BUT_NULL || type == PE_UNSET)
	{
		ft_dprintf(2, "%s: %s: %s\n", SHELL_NAME, self->parameter, self->word);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

int	parameter_expansion_colon_plus_case(t_parameter_expansion *self,
	t_parameter_expansion_type type)
{
	if (type == PE_SET_AND_NOT_NULL)
		substitute_word(self->word, self->replacement);
	return (EXIT_SUCCESS);
}
