/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parameter_expansion_struct.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthan <dthan@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/26 06:53:19 by dthan             #+#    #+#             */
/*   Updated: 2021/01/27 11:37:25 by dthan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void					parameter_expansion_struct_valid_delimeter
	(char ***valid_delimeter)
{
	static char *delimeter[5];

	if (!ft_strequ(delimeter[0], ":-"))
	{
		delimeter[0] = ":-";
		delimeter[1] = ":=";
		delimeter[2] = ":?";
		delimeter[3] = ":+";
		delimeter[4] = NULL;
	}
	*valid_delimeter = delimeter;
}

void					parameter_expansion_struct_needle
	(char needle[256], char *str)
{
	int i;
	int head;
	int tail;

	i = -1;
	head = 0;
	tail = 0;
	while (str[++i])
	{
		if ((str[i] == '$' && is_real_character(str, i))
			&& str[i + 1] && str[i + 1] == '{')
		{
			head = i;
			jump_expansion(str, &i, str[i + 1], NULL);
			tail = i;
			break ;
		}
	}
	i = 0;
	while (head <= tail)
		needle[i++] = str[head++];
}

void					parameter_expansion_struct_expression
	(char expression[256],
		char needle[256])
{
	ft_strcpy(expression, &needle[2]);
	expression[ft_strlen(expression) - 1] = '\0';
}

void					destructor_parameter_expansion_struct
	(t_parameter_expansion *self)
{
	if (self == NULL)
		return ;
	free(self);
}

t_parameter_expansion	*constructor_parameter_expansion_struct
	(char *str)
{
	t_parameter_expansion *self;

	self = (t_parameter_expansion*)ft_memalloc(sizeof(t_parameter_expansion));
	parameter_expansion_struct_valid_delimeter(&self->valid_delimeter);
	parameter_expansion_struct_needle(self->needle, str);
	parameter_expansion_struct_expression(self->expression, self->needle);
	parameter_expansion_struct_split(self);
	if (parameter_expansion_syntax_analysis(self) == EXIT_FAILURE)
	{
		ft_dprintf(2, "%s: %s: bad substitution\n", SHELL_NAME, self->needle);
		destructor_parameter_expansion_struct(self);
		return (NULL);
	}
	if (parameter_expansion_struct_replacement(self->replacement, self) ==
		EXIT_FAILURE)
	{
		destructor_parameter_expansion_struct(self);
		return (NULL);
	}
	return (self);
}
