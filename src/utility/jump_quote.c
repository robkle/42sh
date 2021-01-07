/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jump_quote.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthan <dthan@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/30 06:30:22 by dthan             #+#    #+#             */
/*   Updated: 2021/01/06 20:04:12 by dthan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int jump_quote(char *input, int *i, char quote_type)
{
	(*i)++;
	while (input[*i])
	{
		if (input[*i] == quote_type && is_real_quote(input, *i))
			break;
		(*i)++;
	}
	if (input[*i] == '\0')
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
