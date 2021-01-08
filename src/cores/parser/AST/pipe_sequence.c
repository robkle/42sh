/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_sequence.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthan <dthan@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/11 08:33:28 by dthan             #+#    #+#             */
/*   Updated: 2020/10/28 01:07:26 by dthan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

/*
** pipe_sequence :                             command	1
**               | pipe_sequence '|' linebreak command	2
*/

t_astnode		*pipe_sequence2(t_token **token)
{
	return (command(token));
}

t_astnode		*pipe_sequence1(t_token **token)
{
	t_astnode	*node;
	t_astnode	*lnode;
	t_astnode	*rnode;
	char		*operator;

	if ((lnode = command(token)) == NULL)
		return (NULL);
	if (!*token || (*token)->type != TOKEN_PIPE)
	{
		clear_ast(lnode);
		return (NULL);
	}
	operator = (*token)->data;
	*token = (*token)->next;
	if ((rnode = pipe_sequence(token)) == NULL)
	{
		clear_ast(lnode);
		return (NULL);
	}
	node = build_node(AST_pipe_sequence);
	node->data = ft_strdup(operator);
	node->left = lnode;
	node->right = rnode;
	return (node);
}

t_astnode		*pipe_sequence(t_token **token)
{
	t_astnode	*node;
	t_token		*reset;

	reset = *token;
	if ((node = pipe_sequence1(token)) != NULL)
		return (node);
	*token = reset;
	if ((node = pipe_sequence2(token)) != NULL)
		return (node);
	return (NULL);
}