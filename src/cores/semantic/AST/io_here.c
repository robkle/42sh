/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   io_here.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthan <dthan@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/02 15:46:33 by tango             #+#    #+#             */
/*   Updated: 2021/01/28 13:33:09 by dthan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

t_astnode		*io_here1(t_token **token)
{
	t_astnode	*node;
	t_astnode	*childnode;

	*token = (*token)->next;
	if ((childnode = here_end(token)) == NULL)
		return (NULL);
	node = build_node(AST_io_here);
	node->data = ft_strdup("<<");
	node->left = childnode;
	return (node);
}

t_astnode		*io_here(t_token **token)
{
	if (*token == NULL)
		return (NULL);
	if ((*token)->type == TOKEN_DLESS)
		return (io_here1(token));
	return (NULL);
}
