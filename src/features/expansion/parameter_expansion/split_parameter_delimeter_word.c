/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_parameter_delimeter_word.c                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthan <dthan@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/27 11:07:23 by dthan             #+#    #+#             */
/*   Updated: 2021/01/27 11:39:30 by dthan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int		is_valid_parameter_expansion_delimeter(char *buf,
		char **valid_delimeters)
{
	int i;

	i = -1;
	while (valid_delimeters[++i])
		if (ft_strequ(buf, valid_delimeters[i]))
			return (1);
	return (0);
}

int		parameter_expansion_struct_split_colon
	(t_parameter_expansion *self, int i)
{
	if (is_valid_parameter_expansion_delimeter(self->delimeter,
		self->valid_delimeter))
	{
		i += 2;
		ft_strcpy(self->word, &(self->expression[i]));
		return (EXIT_SUCCESS);
	}
	return (EXIT_FAILURE);
}

int		parameter_expansion_struct_split_hash_percent
	(t_parameter_expansion *self, int i, char type)
{
	self->delimeter[0] = type;
	i++;
	if (self->expression[i] && self->expression[i] == type)
	{
		self->delimeter[1] = type;
		i++;
	}
	ft_strcpy(self->word, &(self->expression[i]));
	return (EXIT_SUCCESS);
}

void	parameter_expansion_struct_split(t_parameter_expansion *self)
{
	int i;

	i = -1;
	while (self->expression[++i])
	{
		if (self->expression[i] == ':' && self->expression[i + 1])
		{
			ft_strncpy(self->delimeter, &(self->expression[i]), 2);
			if (parameter_expansion_struct_split_colon(self, i) == EXIT_SUCCESS)
				break ;
			ft_bzero(self->delimeter, 3);
		}
		else if (i > 0 && (self->expression[i] == '#' ||
				self->expression[i] == '%'))
		{
			parameter_expansion_struct_split_hash_percent(self,
			i, self->expression[i]);
			break ;
		}
		self->parameter[i] = self->expression[i];
	}
}
