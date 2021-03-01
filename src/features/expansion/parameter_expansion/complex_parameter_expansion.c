/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   complex_parameter_expansion.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthan <dthan@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/27 11:05:46 by dthan             #+#    #+#             */
/*   Updated: 2021/02/27 20:44:15 by dthan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int	parameter_expansion_colon_minus_case(
	char parameter[256], char word[256], char replacement[256],
	t_parameter_expansion_type type)
{
	if (type == PE_SET_AND_NOT_NULL)
		substitute_parameter(parameter, replacement);
	else if (type == PE_SET_BUT_NULL || type == PE_UNSET)
		substitute_word(word, replacement);
	return (EXIT_SUCCESS);
}

int	parameter_expansion_colon_equal_case(
	char parameter[256], char word[256], char replacement[256],
	t_parameter_expansion_type type)
{
	if (type == PE_SET_AND_NOT_NULL)
		substitute_parameter(parameter, replacement);
	else if (type == PE_SET_BUT_NULL || type == PE_UNSET)
	{
		assign_word(parameter, word);
		ft_strcpy(replacement, word);
	}
	return (EXIT_SUCCESS);
}

int	parameter_expansion_colon_question_case(
	char parameter[256], char word[256], char replacement[256],
	t_parameter_expansion_type type)
{
	if (type == PE_SET_AND_NOT_NULL)
		substitute_parameter(parameter, replacement);
	else if (type == PE_SET_BUT_NULL || type == PE_UNSET)
	{
		ft_dprintf(2, "%s: %s: %s\n", SHELL_NAME, parameter, word);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

int	parameter_expansion_colon_plus_case(
	char word[256], char replacement[256], t_parameter_expansion_type type)
{
	if (type == PE_SET_AND_NOT_NULL)
		substitute_word(word, replacement);
	return (EXIT_SUCCESS);
}
