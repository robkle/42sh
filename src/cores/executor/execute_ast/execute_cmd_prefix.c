/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmd_prefix.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthan <dthan@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/09 01:51:29 by dthan             #+#    #+#             */
/*   Updated: 2021/01/28 02:43:23 by dthan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	execute_cmd_prefix(t_astnode *ast)
{
	if (ast->type == AST_cmd_prefix)
	{
		execute_assignment_word(ast->left);
		execute_cmd_prefix(ast->right);
	}
	else if (ast->type == AST_ASSIGNMENT_WORD)
		execute_assignment_word(ast);
}
