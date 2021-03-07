/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_errors1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthan <dthan@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/07 02:35:30 by dthan             #+#    #+#             */
/*   Updated: 2021/03/07 02:41:35 by dthan            ###   ########.fr       */
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
