/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_helper2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthan <dthan@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/02 03:00:12 by tango             #+#    #+#             */
/*   Updated: 2021/03/07 02:34:50 by dthan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

/*
** print_token(lst_tokens);
** debugging purpose in lexical_analysis
*/

void	print_token(t_token *token)
{
	while (token)
	{
		ft_putchar('[');
		ft_putstr(token->data);
		ft_putstr("]->");
		token = token->next;
	}
	ft_putstr("NULL\n");
}

void	clear_token(t_token *token)
{
	t_token *temp;

	while (token != NULL)
	{
		temp = token;
		token = token->next;
		free(temp->data);
		free(temp);
	}
}

void	add_token_into_token_list(t_token **token_lst, t_token *new)
{
	t_token *ptr;

	ptr = *token_lst;
	if (ptr == NULL)
		*token_lst = new;
	else
	{
		while (ptr->next)
			ptr = ptr->next;
		ptr->next = new;
	}
}

int		is_made_of_digits(char *data)
{
	int			i;

	i = -1;
	while (data[++i])
		if (!ft_isdigit(data[i]))
			return (0);
	return (1);
}

int		is_assignment_token(char *str, t_token *prev_token)
{
	int i;

	if (prev_token &&
		!is_control_op_not_newline(prev_token->type) &&
		prev_token->type != TOKEN_ASSIGNMENT_WORD)
		return (0);
	i = 0;
	if (!ft_isalpha(str[i]) && str[i] != '_')
		return (0);
	while (str[++i])
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
		{
			if (str[i] == '=')
				return (1);
			return (0);
		}
	}
	return (0);
}
