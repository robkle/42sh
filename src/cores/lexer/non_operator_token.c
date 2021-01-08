/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   non_operator_token.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthan <dthan@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/26 18:51:17 by dthan             #+#    #+#             */
/*   Updated: 2021/01/08 03:49:26 by dthan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

t_token *non_operator_token(char *data, t_token_type type)
{
	t_token *token;
	
	token = (t_token*)malloc(sizeof(t_token));
	token->type = type;
	token->data = data;
	token->next = NULL;
	return (token);
}

t_token	*get_non_operator_token(char *input, int *i)
{
	int head;
	char *str;

	head = *i;
	while (input[*i] && !is_metacharacter(input[*i]) && (input[*i] != '\n'))
	{
		if (input[*i] == '"' && is_real_quote(input, *i))
		{
			if (jump_quote(input, i, input[*i]) == EXIT_FAILURE)
				return (non_operator_token(ft_strdup("\""), TOKEN_BROKEN));
		}
		else if (input[*i] == '\'' && is_real_quote(input, *i))
		{
			if (jump_quote(input, i, input[*i]) == EXIT_FAILURE)
				return (non_operator_token(ft_strdup("\'"), TOKEN_BROKEN));
		}
		else if (input[*i] == '{' && is_real_parameter_expansion(input, *i))
		{
			if (jump_parameter(input, i) == EXIT_FAILURE)
				return (non_operator_token(ft_strdup("{"), TOKEN_BROKEN));
		}
		else if (input[*i] == '\\')
			(*i)++;
		(*i)++;
	}
	str = ft_strndup(&input[head], *i - head);
	if (input[*i] && is_made_of_digits(str) && (input[*i] == '<' || input[*i] == '>'))
		return (non_operator_token(str, TOKEN_IO_NUMBER));
	if (ft_strequ(str, EOF_VALUE))
		return (non_operator_token(str, TOKEN_EOF));
	return (non_operator_token(str, TOKEN_WORD));
}
