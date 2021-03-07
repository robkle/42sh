/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_helper3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthan <dthan@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/07 02:39:04 by dthan             #+#    #+#             */
/*   Updated: 2021/03/07 02:45:24 by dthan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int	is_unsupported_tokens(t_token_type type)
{
	if (type == TOKEN_LESSGREAT || \
		type == TOKEN_DLESSDASH || type == TOKEN_CLOBBER || \
		type == TOKEN_DSEMI || type == TOKEN_OB || \
		type == TOKEN_CB)
		return (1);
	return (0);
}

int	is_near_unexpected_token(t_token *cur_tk, t_token *prev_tk)
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
