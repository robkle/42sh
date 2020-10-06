/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_simple_command.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthan <dthan@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/16 08:39:32 by dthan             #+#    #+#             */
/*   Updated: 2020/10/06 16:56:08 by dthan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void			clear_ast(t_astnode *ast)
{
	//printBinaryTree(ast);
	if (ast->left)
		clear_ast(ast->left);
	if (ast->right)
		clear_ast(ast->right);
	ft_delast(ast);
}

void	execute_simple_command(t_astnode *ast, t_list **heredoc, t_job *j, t_process *p)
{
	if (ast->type == AST_simple_command)
	{
		execute_cmd_name(ast->left, j, p);
		execute_cmd_suffix(ast->right, heredoc, j, p);
	}
	else
		execute_cmd_name(ast, j, p);
	p->status = lauch_process(j, p);
}
