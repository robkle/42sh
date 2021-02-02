/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   complex_parameter_expansion2.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthan <dthan@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/27 12:00:56 by dthan             #+#    #+#             */
/*   Updated: 2021/01/27 12:03:03 by dthan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int	parameter_expansion_percent_case(
	char parameter[256], char word[256], char replacement[256],
	t_parameter_expansion_type type)
{
	if (type == PE_SET_AND_NOT_NULL)
		remove_smallest_or_largest_suffix_pattern(parameter, word, replacement);
	return (EXIT_SUCCESS);
}

int	parameter_expansion_h(
	char parameter[256], char word[256], char replacement[256],
	t_parameter_expansion_type type)
{
	if (type == PE_SET_AND_NOT_NULL)
		remove_smallest_or_largest_prefix_pattern(parameter, word, replacement);
	return (EXIT_SUCCESS);
}
