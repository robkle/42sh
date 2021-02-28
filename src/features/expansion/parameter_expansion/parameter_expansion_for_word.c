/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parameter_expansion_for_word.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthan <dthan@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/28 13:31:29 by dthan             #+#    #+#             */
/*   Updated: 2021/02/28 13:32:29 by dthan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int	parameter_expansion_replace_word(char word[256])
{
	t_parameter_expansion	*ex;
	char					*temp;

	if ((ex = constructor_parameter_expansion_struct(word)) == NULL)
		return (EXIT_FAILURE);
	temp = parameter_expansion_tool_replace(word, ex->needle, ex->replacement);
	ft_strcpy(word, temp);
	(temp) ? free(temp) : 0;
	destructor_parameter_expansion_struct(ex);
	if (is_parameter_expansion(word))
		return (parameter_expansion_replace_word(word));
	return (EXIT_SUCCESS);
}

int	parameter_expansion_for_word(char word[256])
{
	if (ft_strlen(word) == 0)
		return (EXIT_SUCCESS);
	if (is_parameter_expansion(word))
		if (parameter_expansion_replace_word(word) == EXIT_FAILURE)
			return (EXIT_FAILURE);
	if (is_quoted(word))
		remove_quote2(word);
	return (EXIT_SUCCESS);
}
