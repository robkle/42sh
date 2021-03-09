/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simple_command.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthan <dthan@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/11 08:49:46 by dthan             #+#    #+#             */
/*   Updated: 2021/03/09 08:03:20 by dthan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

/*
** simple_command : cmd_prefix cmd_word cmd_suffix		1
**                | cmd_prefix cmd_word					2
**                | cmd_prefix							3
**                | cmd_name cmd_suffix					4
**                | cmd_name							5
*/

t_astnode		*simple_command4(t_token **token)
{
	t_astnode	*node;
	t_astnode	*mnode;
	t_astnode	*rnode;

	if ((mnode = cmd_name(token)) == NULL)
		return (NULL);
	if ((rnode = cmd_suffix(token)) == NULL)
		return (clear_ast(mnode));
	node = build_node(AST_simple_command);
	node->middle = mnode;
	node->right = rnode;
	return (node);
}

t_astnode		*simple_command3(t_token **token)
{
	return (cmd_prefix(token));
}

t_astnode		*simple_command2(t_token **token)
{
	t_astnode *node;
	t_astnode *lnode;
	t_astnode *mnode;

	if ((lnode = cmd_prefix(token)) == NULL)
		return (NULL);
	if ((mnode = cmd_name(token)) == NULL)
		return (clear_ast(lnode));
	node = build_node(AST_simple_command);
	node->left = lnode;
	node->middle = mnode;
	return (node);
}

t_astnode		*simple_command1(t_token **token)
{
	t_astnode *node;
	t_astnode *lnode;
	t_astnode *rnode;
	t_astnode *mnode;

	if ((lnode = cmd_prefix(token)) == NULL)
		return (NULL);
	if ((mnode = cmd_name(token)) == NULL)
		return (clear_ast(lnode));
	if ((rnode = cmd_suffix(token)) == NULL)
	{
		clear_ast(lnode);
		return (clear_ast(mnode));
	}
	node = build_node(AST_simple_command);
	node->left = lnode;
	node->middle = mnode;
	node->right = rnode;
	return (node);
}

t_astnode		*simple_command(t_token **token)
{
	t_astnode	*node;
	t_token		*reset;

	reset = *token;
	if ((node = simple_command1(token)) != NULL)
		return (node);
	*token = reset;
	if ((node = simple_command2(token)) != NULL)
		return (node);
	*token = reset;
	if ((node = simple_command3(token)) != NULL)
		return (node);
	*token = reset;
	if ((node = simple_command4(token)) != NULL)
		return (node);
	*token = reset;
	if ((node = simple_command5(token)) != NULL)
		return (node);
	return (NULL);
}
