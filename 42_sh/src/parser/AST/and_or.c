/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   and_or.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihwang <ihwang@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/11 08:30:42 by dthan             #+#    #+#             */
/*   Updated: 2020/09/06 12:32:31 by ihwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

/*
** and_or	:                         pipeline
**			| and_or AND_IF linebreak pipeline    //not
**        	| and_or OR_IF  linebreak pipeline    //not
*/

t_astnode		*and_or(t_token **token)
{
	t_astnode	*node;
	t_astnode	*lnode;

	if ((lnode = pipeline(token)) == NULL)
		return (NULL);
	if (*token &&
		((*token)->type == TOKEN_AND_IF || (*token)->type == TOKEN_OR_IF))
	{
		node = build_node(AST_and_or);
		node->data = ft_strdup((*token)->data);
		*token = (*token)->next;
		node->left = lnode;
		node->right = and_or(token);
	}
	else
		node = lnode;
	return (node);
	//return (pipeline(token));
}
