/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   io_redirect.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihwang <ihwang@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/11 09:24:37 by dthan             #+#    #+#             */
/*   Updated: 2021/02/04 16:00:24 by ihwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

/*
** io_redirect:           io_file
**            | IO_NUMBER io_file
**            |           io_here
**            | IO_NUMBER io_here
*/

t_astnode	*io_redirect1(t_token **token)
{
	t_astnode	*node;
	t_astnode	*childnode;
	char		*ionumber;

	if (*token == NULL)
		return (NULL);
	if ((*token)->type != TOKEN_IO_NUMBER)
		return (NULL);
	ionumber = (*token)->data;
	*token = (*token)->next;
	if ((childnode = io_file(token)) == NULL)
		return (NULL);
	node = build_node(AST_io_redirect);
	node->data = ft_strdup(ionumber);
	node->left = childnode;
	return (node);
}

t_astnode	*io_redirect2(t_token **token)
{
	return (io_file(token));
}

t_astnode	*io_redirect3(t_token **token)
{
	t_astnode	*node;
	t_astnode	*childnode;
	char		*ionumber;

	if (*token == NULL)
		return (NULL);
	if ((*token)->type != TOKEN_IO_NUMBER)
		return (NULL);
	ionumber = (*token)->data;
	*token = (*token)->next;
	if ((childnode = io_here(token)) == NULL)
		return (NULL);
	node = build_node(AST_io_redirect);
	node->data = ft_strdup(ionumber);
	node->left = childnode;
	return (node);
}

t_astnode	*io_redirect4(t_token **token)
{
	return (io_here(token));
}

t_astnode	*io_redirect(t_token **token)
{
	t_astnode	*node;
	t_token		*reset;

	reset = *token;
	if ((node = io_redirect1(token)) != NULL)
		return (node);
	*token = reset;
	if ((node = io_redirect2(token)) != NULL)
		return (node);
	*token = reset;
	if ((node = io_redirect3(token)) != NULL)
		return (node);
	*token = reset;
	if ((node = io_redirect4(token)) != NULL)
		return (node);
	return (NULL);
}
