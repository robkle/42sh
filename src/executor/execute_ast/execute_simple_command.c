/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_simple_command.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthan <dthan@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/16 08:39:32 by dthan             #+#    #+#             */
/*   Updated: 2020/10/13 12:37:50 by dthan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	execute_simple_command(t_astnode *ast, t_job *j)
{
	t_process *p;

	p = create_process(j);
	if (ast->type == AST_simple_command)
	{
		execute_cmd_name(ast->left, j, p);
		execute_cmd_suffix(ast->right, j, p);
	}
	else
		execute_cmd_name(ast, j, p);
	lauch_simple_command(j, p);
}
