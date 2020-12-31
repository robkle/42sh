/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   non_operator_token.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthan <dthan@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/26 18:51:17 by dthan             #+#    #+#             */
/*   Updated: 2020/12/31 17:41:26 by dthan            ###   ########.fr       */
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
		if ((input[*i] == '"' || input[*i] == '\'') && is_real_quote(input, *i))
			jump_quote(input, i, input[*i]);
		else if (input[*i] == '\\')
			(*i)++;
		(*i)++;
	}
	str = ft_strndup(&input[head], *i - head);
	if (input[*i] && is_made_of_digits(str) && (input[*i] == '<' || input[*i] == '>'))
		return (non_operator_token(str, TOKEN_IO_NUMBER));
	return (non_operator_token(str, TOKEN_WORD));
}
