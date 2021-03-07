/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmd_suffix.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthan <dthan@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/17 11:14:52 by dthan             #+#    #+#             */
/*   Updated: 2021/03/07 16:12:05 by dthan            ###   ########.fr       */
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
			p->av[p->ac - 1] = ft_strdup(ast->left->data);
			p->av[p->ac] = NULL;
			job_command_builder(1, j, p->av[p->ac - 1]);
		}
		else
			execute_io_redirect(ast->left, j, p);
		job_command_builder(1, j, " ");
		execute_cmd_suffix(ast->right, j, p);
	}
	else if (ast->type == AST_WORD)
	{
		p->ac++;
		p->av[p->ac - 1] = ft_strdup(ast->data);
		p->av[p->ac] = NULL;
		job_command_builder(1, j, p->av[p->ac - 1]);
	}
	else
		execute_io_redirect(ast, j, p);
}
