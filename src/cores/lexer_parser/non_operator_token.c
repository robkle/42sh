/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   non_operator_token.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthan <dthan@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/26 18:51:17 by dthan             #+#    #+#             */
/*   Updated: 2021/03/07 01:47:42 by dthan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int		is_inhibitors(char *input, int i, char ch)
{
	if ((ch == '"' || ch == '\'' || ch == '\\') &&
		is_real_character(input, i))
		return (1);
	return (0);
}

int		is_expansion(char *input, int i, char ch)
{
	if (ch == '$' && is_real_character(input, i) &&
		input[i + 1] && (input[i + 1] == '{' || input[i + 1] == '('))
		return (1);
	return (0);
}

t_token	*non_operator_token(char *data, t_token_type type)
{
	t_token *token;

	token = (t_token*)malloc(sizeof(t_token));
	token->type = type;
	token->data = data;
	token->next = NULL;
	return (token);
}

t_token	*select_non_operator_token(
	char *input, int head, int tail, t_token *prev_tk)
{
	char *str;

	str = ft_strndup(&input[head], tail - head);
	if (ft_strequ(str, EOF_VALUE))
		return (non_operator_token(str, TOKEN_EOF));
	if (is_made_of_digits(str) && input[tail] &&
		(input[tail] == '<' || input[tail] == '>'))
		return (non_operator_token(str, TOKEN_IO_NUMBER));
	if (is_assignment_token(str, prev_tk))
		return (non_operator_token(str, TOKEN_ASSIGNMENT_WORD));
	return (non_operator_token(str, TOKEN_WORD));
}

t_token	*get_non_operator_token(char *input, int *i, t_token *prev_tk)
{
	int		head;
	char	temp[2];

	head = *i;
	ft_bzero(temp, 2);
	while (input[*i] && !is_metacharacter(input[*i]) && (input[*i] != '\n'))
	{
		if (is_inhibitors(input, *i, input[*i]))
		{
			temp[0] = input[*i];
			if (jump_quote(input, i, input[*i]) == EXIT_FAILURE)
				return (non_operator_token(ft_strdup(temp), TOKEN_BROKEN));
		}
		else if (is_expansion(input, *i, input[*i]))
		{
			temp[0] = input[*i + 1];
			if (jump_expansion(input, i, input[*i + 1], temp) == EXIT_FAILURE)
				return (non_operator_token(ft_strdup(temp), TOKEN_BROKEN));
		}
		(*i)++;
	}
	return (select_non_operator_token(input, head, *i, prev_tk));
}
