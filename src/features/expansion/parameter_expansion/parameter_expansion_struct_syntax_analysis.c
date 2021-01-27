/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parameter_expansion_struct_syntax_analysis.        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthan <dthan@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/27 11:32:25 by dthan             #+#    #+#             */
/*   Updated: 2021/01/27 11:34:07 by dthan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int		parameter_expansion_syntax_analysis(t_parameter_expansion *self)
{
	if (ft_strlen(self->expression) == 0)
		return (EXIT_FAILURE);
	if (ft_strlen(self->parameter) == 0)
		return (EXIT_FAILURE);
	if (self->parameter[0] == '#' && ft_strlen(self->delimeter) != 0)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
