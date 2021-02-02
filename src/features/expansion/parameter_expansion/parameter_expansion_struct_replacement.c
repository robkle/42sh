/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parameter_expansion_struct_replacement.c           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthan <dthan@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/27 11:34:44 by dthan             #+#    #+#             */
/*   Updated: 2021/01/27 11:59:50 by dthan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int							simple_parameter_expansion(
	char replacement[256], char parameter[256])
{
	char	*temp;
	t_var	*var;

	temp = NULL;
	var = NULL;
	if (ft_strequ("?", parameter))
	{
		temp = ft_itoa(g_shell.exit_status);
		ft_strcpy(replacement, temp);
		free(temp);
	}
	else if (parameter[0] == '#')
	{
		temp = ft_itoa(ft_strlen(&parameter[1]));
		ft_strcpy(replacement, temp);
		free(temp);
	}
	else if (is_intern_var(parameter))
	{
		var = ft_getvar(parameter);
		if (var->value)
			ft_strcpy(replacement, var->value);
	}
	return (EXIT_SUCCESS);
}

t_parameter_expansion_type	find_parameter_replacement_type(
	char parameter[256])
{
	t_var *var;

	var = NULL;
	if (ft_strequ("?", parameter))
		return (PE_SET_AND_NOT_NULL);
	else if (is_intern_var(parameter))
	{
		var = ft_getvar(parameter);
		if (var->value)
			return (PE_SET_AND_NOT_NULL);
		return (PE_SET_BUT_NULL);
	}
	return (PE_UNSET);
}

int							complex_parameter_expansion(
	char replacement[256], char parameter[256], char delimeter[3],
	char word[256])
{
	t_parameter_expansion_type type;

	type = find_parameter_replacement_type(parameter);
	if (ft_strequ(delimeter, ":-"))
		return (parameter_expansion_colon_minus_case(parameter, word,
		replacement, type));
	else if (ft_strequ(delimeter, ":="))
		return (parameter_expansion_colon_equal_case(parameter, word,
		replacement, type));
	else if (ft_strequ(delimeter, ":?"))
		return (parameter_expansion_colon_question_case(parameter, word,
		replacement, type));
	else if (ft_strequ(delimeter, ":+"))
		return (parameter_expansion_colon_plus_case(word, replacement, type));
	else if (ft_strequ(delimeter, "%") || ft_strequ(delimeter, "%%"))
		return (parameter_expansion_percent_case(parameter, word, replacement,
		type));
	else if (ft_strequ(delimeter, "#") || ft_strequ(delimeter, "##"))
		return (parameter_expansion_h(parameter, word, replacement, type));
	return (EXIT_SUCCESS);
}

int							parameter_expansion_struct_replacement(
	char replacement[256], t_parameter_expansion *self)
{
	if (ft_strlen(self->delimeter) == 0)
		return (simple_parameter_expansion(replacement, self->parameter));
	return (complex_parameter_expansion(replacement, self->parameter,
			self->delimeter, self->word));
}
