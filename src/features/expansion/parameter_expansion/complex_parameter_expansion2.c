/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   complex_parameter_expansion2.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthan <dthan@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/27 12:00:56 by dthan             #+#    #+#             */
/*   Updated: 2021/02/28 13:46:04 by dthan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int	parameter_expansion_percent_case(t_parameter_expansion *self,
	t_parameter_expansion_type type)
{
	if (type == PE_SET_AND_NOT_NULL)
		remove_smallest_or_largest_suffix_pattern(self);
	return (EXIT_SUCCESS);
}

int	parameter_expansion_h(t_parameter_expansion *self,
	t_parameter_expansion_type type)
{
	if (type == PE_SET_AND_NOT_NULL)
		remove_smallest_or_largest_prefix_pattern(self);
	return (EXIT_SUCCESS);
}
