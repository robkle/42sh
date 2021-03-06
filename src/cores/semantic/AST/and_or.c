/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   and_or.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthan <dthan@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/11 08:30:42 by dthan             #+#    #+#             */
/*   Updated: 2021/03/06 18:16:46 by dthan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

/*
** and_or	:                         pipeline
**			| and_or AND_IF linebreak pipeline
**        	| and_or OR_IF  linebreak pipeline
*/

t_astnode	*and_or2(t_token **token)
{
	return (pipeline(token));
}

t_astnode	*and_or1(t_token **token)
{
	t_astnode	*node;
	t_astnode	*lnode;
	t_astnode	*rnode;
	char		*operator;

	if ((lnode = pipeline(token)) == NULL)
		return (NULL);
	if (!*token || \
		((*token)->type != TOKEN_AND_IF && (*token)->type != TOKEN_OR_IF))
	{
		clear_ast(lnode);
		return (NULL);
	}
	operator = (*token)->data;
	*token = (*token)->next;
	if (*token && (*token)->type == TOKEN_NEWLINE)
		linebreak(token);
	if ((rnode = and_or(token)) == NULL)
	{
		clear_ast(lnode);
		return (NULL);
	}
	node = build_node(AST_and_or);
	node->left = lnode;
	node->right = rnode;
	node->data = ft_strdup(operator);
	return (node);
}

t_astnode	*and_or(t_token **token)
{
	t_astnode	*node;
	t_token		*reset;

	reset = *token;
	if ((node = and_or1(token)) != NULL)
		return (node);
	*token = reset;
	if ((node = and_or2(token)) != NULL)
		return (node);
	return (NULL);
}
