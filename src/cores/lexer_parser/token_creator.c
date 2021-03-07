/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_creator.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthan <dthan@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/06 14:05:07 by dthan             #+#    #+#             */
/*   Updated: 2021/03/07 16:50:31 by dthan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

t_token	*token_creator_service(char *input, int *i, t_token *prev_tk)
{
	if (input[*i] == ' ' || input[*i] == '\t' || input[*i] == '\n')
	{
		(*i)++;
		if (input[*i - 1] == '\n')
			return (non_operator_token(ft_strdup("newline"), TOKEN_NEWLINE));
		else
			return (NULL);
	}
	else if (is_metacharacter(input[*i]))
		return (get_operator_token(input, i));
	return (get_non_operator_token(input, i, prev_tk));
}
