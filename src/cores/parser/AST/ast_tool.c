/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_tool.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthan <dthan@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/11 07:29:09 by dthan             #+#    #+#             */
/*   Updated: 2021/01/09 02:47:21 by dthan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

t_astnode		*build_node(t_astnode_type type)
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

void			ft_delast(t_astnode *node)
{
	ft_strdel(&(node->data));
	free(node);
}
