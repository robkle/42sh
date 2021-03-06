/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_helper1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthan <dthan@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/13 11:40:09 by dthan             #+#    #+#             */
/*   Updated: 2021/03/06 19:24:32 by dthan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int	is_metacharacter(char chr)
{
	if (chr == '|' || chr == '&' || chr == ';' || \
		chr == '(' || chr == ')' || chr == '<' || \
		chr == '>' || chr == ' ' || chr == '\t')
		return (1);
	return (0);
}

int	is_valid_operator_token(char *str)
{
	if (ft_strequ(str, "&") || ft_strequ(str, ";") || \
		ft_strequ(str, "(") || ft_strequ(str, ")") || \
		ft_strequ(str, "&&") || ft_strequ(str, "||") || \
		ft_strequ(str, ";;") || \
		ft_strequ(str, "<") || ft_strequ(str, ">") || \
		ft_strequ(str, "<<") || ft_strequ(str, ">>") || \
		ft_strequ(str, "<&") || ft_strequ(str, ">&") || \
		ft_strequ(str, "<>") || ft_strequ(str, "<<-") || \
		ft_strequ(str, ">|"))
		return (1);
	return (0);
}

int	is_unsupported_tokens(t_token_type type)
{
	if (type == TOKEN_LESSGREAT || \
		type == TOKEN_DLESSDASH || type == TOKEN_CLOBBER || \
		type == TOKEN_DSEMI || type == TOKEN_OB || \
		type == TOKEN_CB)
		return (1);
	return (0);
}

int	is_control_op_not_newline(t_token_type type)
{
	if (type == TOKEN_SEMI || type == TOKEN_APS || \
		type == TOKEN_PIPE || type == TOKEN_AND_IF || \
		type == TOKEN_OR_IF)
		return (1);
	return (0);
}

int	is_redirect_op(t_token_type type)
{
	if (type == TOKEN_GREAT || type == TOKEN_DGREAT || \
		type == TOKEN_LESS || type == TOKEN_DLESS || \
		type == TOKEN_LESSAND || type == TOKEN_GREATAND)
		return (1);
	return (0);
}

int	is_made_of_digits(char *data)
{
	int			i;

	i = -1;
	while (data[++i])
		if (!ft_isdigit(data[i]))
			return (0);
	return (1);
}

int	is_assignment_token(char *str, t_token *prev_token)
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
