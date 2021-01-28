/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_simple_command.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthan <dthan@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/16 08:39:32 by dthan             #+#    #+#             */
/*   Updated: 2021/01/28 03:43:02 by dthan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void		execute_simple_command1(t_astnode *ast)
{
	execute_cmd_prefix(ast);
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
	(ast->left) ? execute_cmd_prefix(ast->left) : 0;
	(ast->middle) ? execute_cmd_name(ast->middle, j, p) : 0;
	(ast->right) ? execute_cmd_suffix(ast->right, j, p) : 0;
	return (p);
}

void		execute_simple_command(t_astnode *ast, t_job *j)
{
	t_process *p;

	p = NULL;
	if (ast->type == AST_cmd_prefix || ast->type == AST_ASSIGNMENT_WORD)
		execute_simple_command1(ast); //pass job later
	else if (ast->type == AST_WORD)
		p = execute_simple_command2(ast, j);
	else if (ast->type == AST_simple_command)
		p = execute_simple_command3(ast, j);
	if (p != NULL)
		g_shell.exit_status = lauch_simple_command(j, p);
}
