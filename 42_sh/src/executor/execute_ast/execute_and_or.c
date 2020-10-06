/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_and_or.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthan <dthan@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/16 08:35:52 by dthan             #+#    #+#             */
/*   Updated: 2020/10/06 17:02:50 by dthan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

// need to check for the logical AND OR

void	execute_and_or(t_astnode *ast, t_list **heredoc, t_job *job)
{
	if (ast->type == AST_and_or && ft_strequ(ast->data, "&&"))
	{
		// status = execute_pipeline(ast->left, heredoc, job);
		// if (WIFEXITED(status) != 0)
		execute_pipeline(ast->left, heredoc, job);
		execute_and_or(ast->right, heredoc, job);
	}
	else if (ast->type == AST_and_or && ft_strequ(ast->data, "||"))
	{
		// status = execute_pipeline(ast->left, heredoc, job);
		// if (WIFEXITED(status) == 0)
		execute_pipeline(ast->left, heredoc, job);
		execute_and_or(ast->right, heredoc, job);
	}
	else
		return (execute_pipeline(ast, heredoc, job));
}
