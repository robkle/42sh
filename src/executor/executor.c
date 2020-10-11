/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthan <dthan@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/08 08:06:41 by dthan             #+#    #+#             */
/*   Updated: 2020/10/07 02:41:22 by dthan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

// we can use lstdel here

void			executor(t_astnode *ast)
{
	t_list *heredoc;
	t_list	*ptr_heredoc;

	heredoc = NULL;
	printBinaryTree(ast);
	find_heredoc(ast, &heredoc);
	ptr_heredoc = heredoc;
	execute_complete_command(ast, &heredoc);
	clear_heredoc(ptr_heredoc);
	clear_ast(ast);
}
