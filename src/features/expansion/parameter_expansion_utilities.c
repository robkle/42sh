/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parameter_expansion_utilities.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthan <dthan@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/08 03:24:07 by dthan             #+#    #+#             */
/*   Updated: 2021/01/15 14:19:53 by dthan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int jump_parameter(char *input, int *i)
{
	int stack;
	char type;
	char rev_type;

	type = input[++(*i)];
	rev_type = (type == '{') ? '}' : ')';
	stack = 1;
	while (input[++(*i)])
	{
		if (input[*i] == type)
			stack++;
		else if (input[*i] == rev_type)
			stack--;
		if (stack == 0)
			break ;
	}
	if (input[*i] == '\0')
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int is_real_dolar_sign(char *str, int i)
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

// int is_real_parameter_expansion(char *str, int i)
// {
// 	if (i == 0)
// 		return (1);
// 	if (str[--i] != '$')
// 		return (0);
// 	if (is_real_dolar_sign(str, i))
// 		return (1);
// 	return (0);
// }
