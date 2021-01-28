/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_analysis.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthan <dthan@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/12 13:24:09 by dthan             #+#    #+#             */
/*   Updated: 2021/01/28 13:32:05 by dthan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static t_astnode	*build_ast(t_token *token)
{
	return (complete_command(&token));
}

t_astnode			*semantic_analysis(t_token *token)
{
	t_astnode		*abstract_syntax_tree;

	if ((abstract_syntax_tree = build_ast(token)) == NULL)
	{
		return (NULL);
	}
	return (abstract_syntax_tree);
}
