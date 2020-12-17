/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmd_suffix.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthan <dthan@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/17 11:14:52 by dthan             #+#    #+#             */
/*   Updated: 2020/10/28 03:27:47 by dthan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	execute_cmd_suffix(t_astnode *ast, t_job *j, t_process *p)
{
	if (ast->type == AST_cmd_suffix)
	{
		if (ast->left->type == AST_WORD)
		{
			p->ac++;
			p->av[p->ac - 1] = ast->left->data;
			p->av[p->ac] = NULL;
		}
		else
			execute_io_redirect(ast->left ,p);
		execute_cmd_suffix(ast->right, j, p);

	}
	else if (ast->type == AST_WORD)
	{
		p->ac++;
		p->av[p->ac - 1] = ast->data;
		p->av[p->ac] = NULL;
	}
	else
		execute_io_redirect(ast, p);
}
