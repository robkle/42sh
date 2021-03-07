/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_helper1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthan <dthan@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/13 11:40:09 by dthan             #+#    #+#             */
/*   Updated: 2021/03/07 02:45:04 by dthan            ###   ########.fr       */
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

int	is_control_op(t_token_type type)
{
	if (type == TOKEN_SEMI || type == TOKEN_APS || \
		type == TOKEN_PIPE || type == TOKEN_AND_IF || \
		type == TOKEN_OR_IF || type == TOKEN_NEWLINE)
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
