/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_and_or.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthan <dthan@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/16 08:35:52 by dthan             #+#    #+#             */
/*   Updated: 2021/01/28 02:43:01 by dthan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	searching_or_list(
	t_astnode *ast, int foreground, int forked, int noticed)
{
	if (ast->type == AST_and_or && ft_strequ(ast->data, "&&"))
		searching_or_list(ast->right, foreground, forked, noticed);
	else if (ast->type == AST_and_or && ft_strequ(ast->data, "||"))
		execute_and_or(ast->right, foreground, forked, noticed);
}

void	searching_and_list(
	t_astnode *ast, int foreground, int forked, int noticed)
{
	if (ast->type == AST_and_or && ft_strequ(ast->data, "||"))
		searching_and_list(ast->right, foreground, forked, noticed);
	else if (ast->type == AST_and_or && ft_strequ(ast->data, "&&"))
		execute_and_or(ast->right, foreground, forked, noticed);
}

void	execute_and_or(t_astnode *ast, int foreground, int forked, int noticed)
{
	t_job *job;

	job = create_job(foreground, forked);
	if (ast->type == AST_and_or && ft_strequ(ast->data, "&&"))
	{
		(execute_pipeline(ast->left, job) == 0) ?
			execute_and_or(ast->right, foreground, forked, noticed) :
			searching_or_list(ast->right, foreground, forked, noticed);
	}
	else if (ast->type == AST_and_or && ft_strequ(ast->data, "||"))
	{
		(execute_pipeline(ast->left, job) != 0) ?
			execute_and_or(ast->right, foreground, forked, noticed) :
			searching_and_list(ast->right, foreground, forked, noticed);
	}
	else
		execute_pipeline(ast, job);
}
