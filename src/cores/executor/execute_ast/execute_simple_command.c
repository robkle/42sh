/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_simple_command.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthan <dthan@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/16 08:39:32 by dthan             #+#    #+#             */
/*   Updated: 2021/03/07 16:10:51 by dthan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

t_process	*execute_simple_command1(t_astnode *ast, t_job *j)
{
	t_process *p;

	p = create_process(j);
	execute_cmd_prefix(ast, j, p);
	return (p);
}

t_process	*execute_simple_command2(t_astnode *ast, t_job *j)
{
	t_process *p;

	p = create_process(j);
	execute_cmd_name(ast, j, p);
	return (p);
}

t_process	*execute_simple_command3(t_astnode *ast, t_job *j)
{
	t_process *p;

	p = create_process(j);
	(ast->left) ? execute_cmd_prefix(ast->left, j, p) : 0;
	(ast->left) ? job_command_builder(1, j, " ") : 0;
	(ast->middle) ? execute_cmd_name(ast->middle, j, p) : 0;
	(ast->middle) ? job_command_builder(1, j, " ") : 0;
	(ast->right) ? execute_cmd_suffix(ast->right, j, p) : 0;
	return (p);
}

int			is_io_redirect_parts(t_astnode *ast)
{
	if (ast == NULL)
		return (0);
	if (ast->type == AST_io_redirect ||
		ast->type == AST_io_file ||
		ast->type == AST_io_here)
		return (1);
	return (0);
}

void		execute_simple_command(t_astnode *ast, t_job *j)
{
	t_process *p;

	p = NULL;
	if (ast->type == AST_cmd_prefix || ast->type == AST_ASSIGNMENT_WORD ||
		is_io_redirect_parts(ast))
		p = execute_simple_command1(ast, j);
	else if (ast->type == AST_WORD)
		p = execute_simple_command2(ast, j);
	else if (ast->type == AST_simple_command)
		p = execute_simple_command3(ast, j);
	g_shell.exit_status = lauch_simple_command(j, p);
}
