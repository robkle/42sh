/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_cm_string.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthan <dthan@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/27 12:57:38 by dthan             #+#    #+#             */
/*   Updated: 2021/01/28 01:48:25 by dthan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	build_simple_command_command(t_astnode *ast, t_job *j)
{
	if (ast->type == AST_cmd_prefix || ast->type == AST_ASSIGNMENT_WORD)
		build_command_prefix_command(ast, j);
	else if (ast->type == AST_WORD)
		build_command_name_command(ast, j);
	else if (ast->type == AST_simple_command)
	{
		if (ast->left)
			build_command_prefix_command(ast->left, j);
		if (ast->middle)
		{
			if (ast->left)
				job_command_builder(1, j, " ");
			build_command_name_command(ast->middle, j);
		}
		if (ast->right)
		{
			job_command_builder(1, j, " ");
			build_command_suffix_command(ast->right, j);
		}
	}
}

void	build_pipe_sequence_command(t_astnode *ast, t_job *j)
{
	if (ast->type == AST_pipe_sequence)
	{
		build_simple_command_command(ast->left, j);
		job_command_builder(1, j, " | ");
		build_pipe_sequence_command(ast->right, j);
	}
	else
		build_simple_command_command(ast, j);
}

void	build_and_or_command(t_astnode *ast, t_job *j)
{
	if (ast->type == AST_and_or)
	{
		build_pipe_sequence_command(ast->left, j);
		job_command_builder(3, j, " ", ast->data, " ");
		build_and_or_command(ast->right, j);
	}
	else
		build_pipe_sequence_command(ast, j);
}
