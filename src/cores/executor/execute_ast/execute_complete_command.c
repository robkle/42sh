/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_complete_command.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthan <dthan@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/16 08:30:58 by dthan             #+#    #+#             */
/*   Updated: 2020/10/28 01:05:56 by dthan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	execute_complete_command(t_astnode *ast)
{
	if (ast->type == AST_complete_command)
	{
		if (ft_strequ(ast->data, "&"))
			execute_list(ast->left, 0);
		else
			execute_list(ast->left, 1);
	}
	else
		execute_list(ast, 1);
}
