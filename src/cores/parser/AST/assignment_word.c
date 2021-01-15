/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assignment_word.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthan <dthan@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/09 01:29:04 by dthan             #+#    #+#             */
/*   Updated: 2021/01/09 01:49:20 by dthan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

t_astnode	*assignment_word(t_token **token)
{
	t_astnode *node;

	if (*token == NULL)
		return (NULL);
	if ((*token)->type != TOKEN_ASSIGNMENT_WORD)
		return (NULL);
	node = build_node(AST_ASSIGNMENT_WORD);
	node->data = ft_strdup((*token)->data);
	node->left = NULL;
	node->right = NULL;
	node->middle = NULL;
	*token = (*token)->next;
	return (node);
}
