/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_tool.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthan <dthan@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/11 07:29:09 by dthan             #+#    #+#             */
/*   Updated: 2021/02/27 23:01:24 by dthan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

t_astnode	*build_node(t_astnode_type type)
{
	t_astnode	*node;

	node = (t_astnode*)malloc(sizeof(t_astnode));
	node->data = NULL;
	node->type = type;
	node->left = NULL;
	node->right = NULL;
	node->middle = NULL;
	return (node);
}

void		ft_delast(t_astnode *node)
{
	ft_strdel(&(node->data));
	free(node);
}

void		clear_ast(t_astnode *ast)
{
	if (ast->left)
		clear_ast(ast->left);
	if (ast->middle)
		clear_ast(ast->middle);
	if (ast->right)
		clear_ast(ast->right);
	ft_delast(ast);
}
