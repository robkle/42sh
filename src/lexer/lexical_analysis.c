/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexical_analysis.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthan <dthan@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/09 08:37:27 by dthan             #+#    #+#             */
/*   Updated: 2020/10/27 05:38:03 by dthan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static int control_ops_issue(t_token *curr, t_token *prev)
{
	if (!is_control_op_not_newline(curr->type))
		return (0);
	if (!prev)
		return (1);
	if (is_control_op_not_newline(prev->type))
		return (1);
	return (0);
}

static int redirect_ops_issue(t_token *curr, t_token *prev)
{
	if (!prev)
		return (0);
	if (is_redirect_op(prev->type) && \
		(is_redirect_op(curr->type) || \
		is_control_op_not_newline(curr->type) ||
		curr->type == TOKEN_NEWLINE))
		return (1);
	return (0);
}

int parser(t_token *curr, t_token *prev)
{
	if (is_unsupported_tokens(curr->type))
	{
		ft_dprintf(2, "%s: Unsupported token `%s`\n", "42sh", curr->data); // need to change value
		return (0);
	}
	if (!prev && is_redirect_op(curr->type))
	{
		ft_dprintf(2, "%s: Unsupported cmd_prefix\n", "42sh"); // need to change value
		return (0);
	}
	if (control_ops_issue(curr, prev) || \
		redirect_ops_issue(curr, prev))
	{
		ft_dprintf(2, "%s: syntax error near unexpected token `%s'\n", "42sh", curr->data);
		return (0);
	}
	return(1);
}

t_token			*lexer_and_parser(char *input)
{
	t_token		*token_lst;
	t_token		*current_token;
	t_token		*prev_token;
	int			i;

	i = 0;
	token_lst = NULL;
	prev_token = NULL;
	while (input[i])
	{
		if (input[i] == '\n')
		{
			current_token = non_operator_token(ft_strdup("newline"), TOKEN_NEWLINE);
			i++;
		}
		else if (is_metacharacter(input[i]))
		{
			if (input[i] == ' ' || input[i] == '\t')
			{
				i++;
				continue;
			}
			current_token = get_operator_token(input, &i);
		}
		else
			current_token = get_non_operator_token(input, &i);
		if (alias_substitution(current_token, &prev_token, &token_lst) != 1)
		{
			add_token_into_token_list(&token_lst, current_token);
			if (!parser(current_token, prev_token))
			{
				clear_token(token_lst);
				return (NULL);
			}
			prev_token = current_token;
		}
		
	}
	print_token(token_lst);
	return (token_lst);
}
