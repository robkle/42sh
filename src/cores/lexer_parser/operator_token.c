/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operator_token.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthan <dthan@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/26 18:50:57 by dthan             #+#    #+#             */
/*   Updated: 2021/03/06 19:25:33 by dthan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static t_token_type	get_redirection_token_type(char *data)
{
	if (ft_strequ(data, "<"))
		return (TOKEN_LESS);
	else if (ft_strequ(data, ">"))
		return (TOKEN_GREAT);
	else if (ft_strequ(data, "<<"))
		return (TOKEN_DLESS);
	else if (ft_strequ(data, ">>"))
		return (TOKEN_DGREAT);
	else if (ft_strequ(data, "<&"))
		return (TOKEN_LESSAND);
	else if (ft_strequ(data, ">&"))
		return (TOKEN_GREATAND);
	else if (ft_strequ(data, "<>"))
		return (TOKEN_LESSGREAT);
	else if (ft_strequ(data, "<<-"))
		return (TOKEN_DLESSDASH);
	return (TOKEN_CLOBBER);
}

static t_token_type	get_token_type(char *data)
{
	if (ft_strequ(data, ";"))
		return (TOKEN_SEMI);
	else if (ft_strequ(data, "&"))
		return (TOKEN_APS);
	else if (ft_strequ(data, "|"))
		return (TOKEN_PIPE);
	else if (ft_strequ(data, "("))
		return (TOKEN_OB);
	else if (ft_strequ(data, ")"))
		return (TOKEN_CB);
	else if (ft_strequ(data, "&&"))
		return (TOKEN_AND_IF);
	else if (ft_strequ(data, "||"))
		return (TOKEN_OR_IF);
	else if (ft_strequ(data, ";;"))
		return (TOKEN_DSEMI);
	return (get_redirection_token_type(data));
}

static t_token		*operator_token(char *data)
{
	t_token *token;

	token = (t_token*)malloc(sizeof(t_token));
	token->data = ft_strdup(data);
	token->type = get_token_type(data);
	token->next = NULL;
	return (token);
}

t_token				*get_operator_token(char *input, int *i)
{
	char	token_recognizer[4];
	int		j;

	j = 0;
	ft_bzero(token_recognizer, 4);
	while (input[*i] && j < 3)
	{
		token_recognizer[j] = input[*i];
		if (j > 0)
		{
			if (!is_valid_operator_token(token_recognizer))
			{
				token_recognizer[j] = 0;
				break ;
			}
		}
		j++;
		(*i)++;
	}
	return (operator_token(token_recognizer));
}
