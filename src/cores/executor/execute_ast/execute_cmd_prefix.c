/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmd_prefix.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthan <dthan@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/09 01:51:29 by dthan             #+#    #+#             */
/*   Updated: 2021/02/25 06:11:34 by dthan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	execute_cmd_prefix(t_astnode *ast, t_job *j, t_process *p)
{
	if (ast->type == AST_cmd_prefix)
	{
		if (ast->left->type == AST_ASSIGNMENT_WORD)
		{
			execute_assignment_word(ast->left, p);
			job_command_builder(1, j, ast->left->data);
		}
		else
			execute_io_redirect(ast->left, j, p);
		job_command_builder(1, j, " ");
		execute_cmd_prefix(ast->right, j, p);
	}
	else if (ast->type == AST_ASSIGNMENT_WORD)
	{
		execute_assignment_word(ast, p);
		job_command_builder(1, j, ast->data);
	}
	else
		execute_io_redirect(ast, j, p);
}
