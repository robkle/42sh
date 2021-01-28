/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthan <dthan@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/08 08:06:41 by dthan             #+#    #+#             */
/*   Updated: 2021/01/28 03:01:14 by dthan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	clear_ast(t_astnode *ast)
{
	if (ast->left)
		clear_ast(ast->left);
	if (ast->right)
		clear_ast(ast->right);
	ft_delast(ast);
}

void	executor(t_astnode *ast)
{
	execute_complete_command(ast);
}
