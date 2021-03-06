/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_analysis.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthan <dthan@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/06 14:00:01 by dthan             #+#    #+#             */
/*   Updated: 2021/03/06 19:22:10 by dthan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int		syntax_error_unexpected_end_of_file(void)
{
	ft_dprintf(2, "%s: syntax error: unexpected end of file\n", SHELL_NAME);
	g_shell.exit_status = 258;
	return (EXIT_FAILURE);
}

int		syntax_error_unsupported_token(char *str)
{
	ft_dprintf(2, "%s: Unsupported token `%s`\n", "42sh", str);
	g_shell.exit_status = 258;
	return (EXIT_FAILURE);
}

int		syntax_error_near_unexpected_token(char *str)
{
	ft_dprintf(2, "%s: syntax error near unexpected token `%s'\n", "42sh", str);
	g_shell.exit_status = 258;
	return (EXIT_FAILURE);
}

int		syntax_error_broken_token(char *str)
{
	ft_dprintf(2, "%s: unexpected EOF while looking for matching `%s'\n",
	SHELL_NAME, str);
	ft_dprintf(2, "%s: syntax error: unexpected end of file\n", SHELL_NAME);
	g_shell.exit_status = 258;
	return (EXIT_FAILURE);
}

int		is_control_op(t_token_type type)
{
	if (type == TOKEN_SEMI || type == TOKEN_APS || \
		type == TOKEN_PIPE || type == TOKEN_AND_IF || \
		type == TOKEN_OR_IF || type == TOKEN_NEWLINE)
		return (1);
	return (0);
}

int		is_near_unexpected_token(t_token *cur_tk, t_token *prev_tk)
{
	if (prev_tk == NULL)
	{
		if (is_control_op(cur_tk->type))
			return (EXIT_FAILURE);
	}
	else
	{
		if ((is_control_op_not_newline(prev_tk->type) &&
			is_control_op_not_newline(cur_tk->type)) ||
			(is_redirect_op(prev_tk->type) && is_redirect_op(cur_tk->type)) ||
			(is_redirect_op(prev_tk->type) && cur_tk->type == TOKEN_NEWLINE))
			return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

int		analyzing_pair_tokens(t_token *tk, t_token *prev_tk)
{
	if (tk->type == TOKEN_EOF)
		return (syntax_error_unexpected_end_of_file());
	if (tk->type == TOKEN_BROKEN)
		return (syntax_error_broken_token(tk->data));
	if (is_unsupported_tokens(tk->type))
		return (syntax_error_unsupported_token(tk->data));
	if (is_near_unexpected_token(tk, prev_tk))
		return (syntax_error_near_unexpected_token(tk->data));
	return (EXIT_SUCCESS);
}

void	init_syntax_service_struct(t_syntax_service *self, t_token *head)
{
	self->cur_tk = head;
	self->prev_tk = NULL;
}

int		syntax_analysis_service(t_token *token_stream)
{
	t_syntax_service instance;

	init_syntax_service_struct(&instance, token_stream);
	while (instance.cur_tk)
	{
		if (analyzing_pair_tokens(
			instance.cur_tk, instance.prev_tk) == EXIT_FAILURE)
			return (EXIT_FAILURE);
		instance.prev_tk = instance.cur_tk;
		instance.cur_tk = instance.cur_tk->next;
	}
	return (EXIT_SUCCESS);
}
