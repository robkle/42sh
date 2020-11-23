/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_helper2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthan <dthan@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/02 03:00:12 by tango             #+#    #+#             */
/*   Updated: 2020/10/26 18:52:42 by dthan            ###   ########.fr       */
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

	while (token)
	{
		ft_strdel(&token->data);
		temp = token;
		token = token->next;
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
