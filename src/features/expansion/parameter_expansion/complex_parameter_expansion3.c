/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   complex_parameter_expansion3.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthan <dthan@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/28 13:01:13 by dthan             #+#    #+#             */
/*   Updated: 2021/02/28 14:01:29 by dthan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int		remove_smallest_suffix_pattern(char replacement[256], char word[256])
{
	ft_strrev(replacement);
	ft_strrev(word);
	if (remove_smallest_prefix_pattern(replacement, word) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	ft_strrev(replacement);
	return (EXIT_SUCCESS);
}

int		remove_largest_suffix_pattern(char replacement[256], char word[256])
{
	ft_strrev(replacement);
	ft_strrev(word);
	if (remove_largest_prefix_pattern(replacement, word) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	ft_strrev(replacement);
	return (EXIT_SUCCESS);
}

void	remove_smallest_or_largest_suffix_pattern(t_parameter_expansion *self)
{
	char orig[256];

	ft_bzero(orig, 256);
	substitute_parameter(self->parameter, self->replacement);
	ft_strcpy(orig, self->replacement);
	if (ft_strequ(self->delimeter, "%"))
	{
		if (remove_smallest_suffix_pattern(
			self->replacement, self->word) == EXIT_FAILURE)
			ft_strcpy(self->replacement, orig);
	}
	else
	{
		if (remove_largest_suffix_pattern(
			self->replacement, self->word) == EXIT_FAILURE)
			ft_strcpy(self->replacement, orig);
	}
}
