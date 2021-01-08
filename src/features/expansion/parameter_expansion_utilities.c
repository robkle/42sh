/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parameter_expansion_utilities.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthan <dthan@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/08 03:24:07 by dthan             #+#    #+#             */
/*   Updated: 2021/01/08 03:36:45 by dthan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int jump_parameter(char *input, int *i)
{
	char stack[10];
	int pos_stack;

	ft_bzero(stack, 10);
	pos_stack = 0;
	stack[pos_stack++] = '{';
	(*i)++;
	while (input[*i])
	{
		if (input[*i] == '{')
			stack[pos_stack++] = '{';
		else if (input[*i] == '}')
			stack[--pos_stack] = '\0';
		if (pos_stack == 0 && stack[pos_stack] == '\0')
			break ;
		(*i)++;
	}
	if (input[*i] == '\0')
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

static int is_real_dolar_sign(char *str, int i)
{
	int ct;

	if (i == 0)
		return (1);
	ct = 0;
	while (i-- >= 0 && str[i] == '\\')
		ct++;
	if (ct % 2 == 0)
		return (1);
	return (0);
}

int is_real_parameter_expansion(char *str, int i)
{
	if (i < 1)
		return (0);
	if (str[--i] != '$')
		return (0);
	if (is_real_dolar_sign(str, i))
		return (1);
	return (0);
}
