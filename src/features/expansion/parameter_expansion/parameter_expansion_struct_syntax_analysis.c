/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parameter_expansion_struct_syntax_analysis.        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthan <dthan@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/27 11:32:25 by dthan             #+#    #+#             */
/*   Updated: 2021/02/15 18:57:37 by dthan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int		parameter_expansion_syntax_analysis_parameter(char parameter[256])
{
	int i;

	if (ft_strlen(parameter) == 0)
		return (EXIT_FAILURE);
	if (ft_strequ(parameter, "?"))
		return (EXIT_SUCCESS);
	if(parameter[0] != '#' && !ft_isalnum(parameter[0]))
		return (EXIT_FAILURE);
	if (parameter[1])
	{
		i = 0;
		while (parameter[++i])
			if (!ft_isalnum(parameter[i]))
				return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

int		parameter_expansion_syntax_analysis_delimeter(char parameter[256], char delimeter[3])
{
	if (parameter[0] == '#' && ft_strlen(delimeter) != 0)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int		parameter_expansion_syntax_analysis_word(char word[256])
{
	int i;

	if (ft_strlen(word) != 0)
	{
		i = -1;
		while (word[++i])
			if (!ft_isalnum(word[i]))
				return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

int		parameter_expansion_syntax_analysis(t_parameter_expansion *self)
{
	if (ft_strlen(self->expression) == 0)
		return (EXIT_FAILURE);
	if (parameter_expansion_syntax_analysis_parameter(
		self->parameter) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (parameter_expansion_syntax_analysis_delimeter(
		self->parameter, self->delimeter) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (parameter_expansion_syntax_analysis_word(self->word) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
