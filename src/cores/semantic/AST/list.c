/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthan <dthan@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/11 07:38:19 by dthan             #+#    #+#             */
/*   Updated: 2021/03/07 19:02:04 by dthan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

/*
** list : list separator_op and_or	1
**    	|                   and_or	2
*/

t_astnode		*list2(t_token **token)
{
	return (and_or(token));
}

t_astnode		*list1(t_token **token)
{
	t_astnode	*node;
	t_astnode	*lnode;
	t_astnode	*rnode;
	char		*operator;

	if ((lnode = and_or(token)) == NULL)
		return (NULL);
	if (!*token ||
		((*token)->type != TOKEN_APS && (*token)->type != TOKEN_SEMI))
		return (clear_ast(lnode));
	operator = (*token)->data;
	*token = (*token)->next;
	if ((rnode = list(token)) == NULL)
		return (clear_ast(lnode));
	node = build_node(AST_list);
	node->left = lnode;
	node->right = rnode;
	node->data = ft_strdup(operator);
	return (node);
}

t_astnode		*list(t_token **token)
{
	t_astnode	*node;
	t_token		*reset;

	reset = *token;
	if ((node = list1(token)) != NULL)
		return (node);
	*token = reset;
	if ((node = list2(token)) != NULL)
		return (node);
	return (NULL);
}
