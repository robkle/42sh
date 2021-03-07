/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_prefix.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthan <dthan@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/09 01:23:55 by dthan             #+#    #+#             */
/*   Updated: 2021/03/07 19:00:16 by dthan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

/*
** cmd_prefix	:			 ASSIGNMENT_WORD
**				| cmd_prefix ASSIGNMENT_WORD
**				|			 io_redirect
**				| cmd_prefix io_redirect
*/

t_astnode		*cmd_prefix1(t_token **token)
{
	t_astnode *node;
	t_astnode *lnode;
	t_astnode *rnode;

	if ((lnode = assignment_word(token)) == NULL)
		return (NULL);
	if ((rnode = cmd_prefix(token)) == NULL)
		return (clear_ast(lnode));
	node = build_node(AST_cmd_prefix);
	node->left = lnode;
	node->right = rnode;
	return (node);
}

t_astnode		*cmd_prefix2(t_token **token)
{
	return (assignment_word(token));
}

t_astnode		*cmd_prefix3(t_token **token)
{
	t_astnode *node;
	t_astnode *lnode;
	t_astnode *rnode;

	if ((lnode = io_redirect(token)) == NULL)
		return (NULL);
	if ((rnode = cmd_prefix(token)) == NULL)
		return (clear_ast(lnode));
	node = build_node(AST_cmd_prefix);
	node->left = lnode;
	node->right = rnode;
	return (node);
}

t_astnode		*cmd_prefix4(t_token **token)
{
	return (io_redirect(token));
}

t_astnode		*cmd_prefix(t_token **token)
{
	t_astnode	*node;
	t_token		*reset;

	reset = *token;
	if ((node = cmd_prefix1(token)) != NULL)
		return (node);
	*token = reset;
	if ((node = cmd_prefix2(token)) != NULL)
		return (node);
	*token = reset;
	if ((node = cmd_prefix3(token)) != NULL)
		return (node);
	*token = reset;
	if ((node = cmd_prefix4(token)) != NULL)
		return (node);
	return (NULL);
}
