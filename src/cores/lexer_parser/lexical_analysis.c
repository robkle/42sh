/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexical_analysis.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthan <dthan@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/09 08:37:27 by dthan             #+#    #+#             */
/*   Updated: 2021/01/23 10:26:35 by dthan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static int	control_ops_issue(t_token *curr, t_token *prev)
{
	if (!is_control_op_not_newline(curr->type))
		return (0);
	if (!prev)
		return (1);
	if (is_control_op_not_newline(prev->type))
		return (1);
	return (0);
}

static int	redirect_ops_issue(t_token *curr, t_token *prev)
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

int			syntax_analysis(t_token *curr, t_token *prev)
{
	if (curr->type == TOKEN_EOF)
	{
		ft_dprintf(2, "%s: syntax error: unexpected end of file\n", SHELL_NAME);
		g_shell.exit_status = 258;
		return (EXIT_FAILURE);
	}
	if (curr->type == TOKEN_BROKEN)
	{
		ft_dprintf(2, "%s: unexpected EOF while looking for matching `%s'\n", SHELL_NAME, curr->data);
		ft_dprintf(2, "%s: syntax error: unexpected end of file\n", SHELL_NAME);
		g_shell.exit_status = 258;
		return (EXIT_FAILURE);	
	}
	if (is_unsupported_tokens(curr->type))
	{
		ft_dprintf(2, "%s: Unsupported token `%s`\n", "42sh", curr->data); // need to change value
		g_shell.exit_status = 258;
		return (EXIT_FAILURE);
	}
	if (!prev && is_redirect_op(curr->type))
	{
		ft_dprintf(2, "%s: Unsupported cmd_prefix\n", "42sh"); // need to change value
		g_shell.exit_status = 258;
		return (EXIT_FAILURE);
	}
	if (control_ops_issue(curr, prev) || \
		redirect_ops_issue(curr, prev))
	{
		ft_dprintf(2, "%s: syntax error near unexpected token `%s'\n", "42sh", curr->data);
		g_shell.exit_status = 258;
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

t_lex_value lex_continue_or_not(t_token *pre_token, t_lex_value lex_value)
{
	if (!pre_token && lex_value == LEX_CMD)
		return (LEX_SUCCESS);
	if (!pre_token && lex_value != LEX_CMD)
		return (lex_value);
	if (pre_token->type == TOKEN_AND_IF)
		return (LEX_CMDAND);
	else if (pre_token->type == TOKEN_OR_IF)
		return (LEX_CMDOR);
	else if (pre_token->type == TOKEN_PIPE)
		return (LEX_PIPE);
	return (LEX_SUCCESS);
}

t_lex_value  lexical_analysis_and_syntax_analysis(char *cmd, t_token **tk_lst, t_lex_value lex_value)
{
	t_token		*current_token;
	t_token		*prev_token;
	int			i;

	i = 0;
	prev_token = NULL;
	while (cmd[i])
	{
		if (cmd[i] == '\n')
		{
			current_token = non_operator_token(ft_strdup("newline"), TOKEN_NEWLINE);
			i++;
		}
		else if (is_metacharacter(cmd[i]))
		{
			if (cmd[i] == ' ' || cmd[i] == '\t')
			{
				i++;
				continue;
			}
			current_token = get_operator_token(cmd, &i);
		}
		else
			current_token = get_non_operator_token(cmd, &i);
		if (current_token->type == TOKEN_WORD && is_assignment_token(current_token->data, prev_token))
			current_token->type = TOKEN_ASSIGNMENT_WORD;
		if (current_token->type == TOKEN_WORD && is_alias(current_token->data, prev_token))
		{
			alias_substitution(&current_token, &prev_token, tk_lst);
			if (current_token == NULL)
				continue ;
		}
		else if (current_token->type != TOKEN_NEWLINE)
			add_token_into_token_list(tk_lst, current_token);
		if (syntax_analysis(current_token, prev_token) == EXIT_FAILURE)
			return (LEX_FAILURE);
		if (current_token->type == TOKEN_NEWLINE)
			clear_token(current_token);
		else
			prev_token = current_token;
	}
	return (lex_continue_or_not(prev_token, lex_value));
}
