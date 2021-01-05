/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthan <dthan@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/08 08:06:41 by dthan             #+#    #+#             */
/*   Updated: 2021/01/05 15:53:13 by dthan            ###   ########.fr       */
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

//we can use lstdel here

void	executor(t_astnode *ast)
{
	// t_heredoc *heredoclist;

	// heredoclist = NULL;
	printBinaryTree(ast);
	// find_heredoc(ast);
	// heredoclist = g_shell.first_heredoc;
	execute_complete_command(ast);
	// clear_heredoc(heredoclist);
	clear_ast(ast);
}
