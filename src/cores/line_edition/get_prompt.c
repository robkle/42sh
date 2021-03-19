/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_prompt.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihwang <ihwang@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/02 15:30:45 by tango             #+#    #+#             */
/*   Updated: 2021/03/19 23:29:01 by rklein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int			prompt_len(t_prompt prompt_type)
{
	if (prompt_type == PROMPT_CMD)
		return (ft_strlen("> "));
	else if (prompt_type == PROMPT_CMD_AND)
		return (ft_strlen("cmdand> "));
	else if (prompt_type == PROMPT_CMD_OR)
		return (ft_strlen("cmdor> "));
	else if (prompt_type == PROMPT_PIPE)
		return (ft_strlen("pipe> "));
	else if (prompt_type == PROMPT_HEREDOC)
		return (ft_strlen("heredoc >"));
	else if (prompt_type == PROMPT_DQUOTE)
		return (ft_strlen("dquote> "));
	else if (prompt_type == PROMPT_QUOTE)
		return (ft_strlen("quote> "));
	else if (prompt_type == PROMPT_BACKSLASH)
		return (ft_strlen("> "));
	else if (prompt_type == PROMPT_CMDSUBST)
		return (ft_strlen("cmdsubst> "));
	else if (prompt_type == PROMPT_BRACEPARAM)
		return (ft_strlen("braceparam> "));
	return (ft_strlen("> "));
}

t_prompt	choose_prompt_type_lex(t_lex_value lex)
{
	if (lex == LEX_CMD)
		return (PROMPT_CMD);
	else if (lex == LEX_CMDAND)
		return (PROMPT_CMD_AND);
	else if (lex == LEX_CMDOR)
		return (PROMPT_CMD_OR);
	else if (lex == LEX_PIPE)
		return (PROMPT_PIPE);
	return (PROMPT_CMD);
}

t_prompt	choose_prompt_type_phase(t_phase phase)
{
	if (phase == PHASE_CMD)
		return (PROMPT_CMD);
	else if (phase == PHASE_DQUOTE)
		return (PROMPT_DQUOTE);
	else if (phase == PHASE_QUOTE)
		return (PROMPT_QUOTE);
	else if (phase == PHASE_BACKSLASH)
		return (PROMPT_BACKSLASH);
	else if (phase == PHASE_CMDSUBST)
		return (PROMPT_CMDSUBST);
	else if (phase == PHASE_BRACEPARAM)
		return (PROMPT_BRACEPARAM);
	return (PROMPT_CMD);
}

t_prompt	choose_prompt_type(t_lex_value lex, t_phase phase)
{
	if (lex > 1)
		return (choose_prompt_type_lex(lex));
	return (choose_prompt_type_phase(phase));
}
