/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihwang <ihwang@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/11 09:17:44 by dthan             #+#    #+#             */
/*   Updated: 2021/02/04 16:00:48 by ihwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

t_astnode		*word(t_token **token)
{
	t_astnode	*node;

	if (*token == NULL)
		return (NULL);
	if ((*token)->type != TOKEN_WORD)
		return (NULL);
	node = build_node(AST_WORD);
	node->data = ft_strdup((*token)->data);
	node->left = NULL;
	node->right = NULL;
	*token = (*token)->next;
	return (node);
}
