/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_list.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthan <dthan@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/16 08:35:21 by dthan             #+#    #+#             */
/*   Updated: 2020/12/18 18:16:11 by dthan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void		execute_list(t_astnode *ast, int foreground)
{
	if (ast->type == AST_list)
	{
		(!foreground && ast->left->type == AST_and_or) ? \
			execute_and_or_bg(ast->left) :
			execute_and_or(ast->left, foreground, 0, 1);
		(ft_strequ(ast->data, "&")) ?
			execute_list(ast->right, 0) : \
			execute_list(ast->right, 1);
	}
	else if (!foreground && ast->type == AST_and_or)
		execute_and_or_bg(ast);
	else
		execute_and_or(ast, foreground, 0, 1);
}
