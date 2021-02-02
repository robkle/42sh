/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_cm_string2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthan <dthan@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/28 01:47:34 by dthan             #+#    #+#             */
/*   Updated: 2021/01/28 01:48:27 by dthan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	build_command_prefix_command(t_astnode *ast, t_job *j)
{
	if (ast->type == AST_cmd_prefix)
	{
		job_command_builder(2, j, ast->left->data, " ");
		build_command_prefix_command(ast->right, j);
	}
	else if (ast->type == AST_ASSIGNMENT_WORD)
		job_command_builder(1, j, ast->data);
}

void	build_command_name_command(t_astnode *ast, t_job *j)
{
	if (ast->type == AST_WORD)
		job_command_builder(1, j, ast->data);
}

void	build_command_io_here_file_command(t_astnode *ast, t_job *j)
{
	if (ast->type == AST_io_here || ast->type == AST_io_file)
		job_command_builder(3, j, ast->data, " ", ast->left->data);
}

void	build_command_io_redirect_command(t_astnode *ast, t_job *j)
{
	if (ast->type == AST_io_redirect)
	{
		job_command_builder(1, j, ast->data);
		build_command_io_here_file_command(ast->left, j);
	}
	else if (ast->type == AST_io_here || ast->type == AST_io_file)
		build_command_io_here_file_command(ast, j);
}

void	build_command_suffix_command(t_astnode *ast, t_job *j)
{
	if (ast->type == AST_WORD)
		job_command_builder(1, j, ast->data);
	else if (ast->type == AST_cmd_suffix)
	{
		job_command_builder(1, j, " ");
		if (ast->left->type == AST_WORD)
			job_command_builder(1, j, ast->left->data);
		else
			build_command_io_redirect_command(ast->left, j);
		job_command_builder(1, j, " ");
		build_command_suffix_command(ast->right, j);
	}
	else
		build_command_io_redirect_command(ast, j);
}
