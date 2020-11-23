/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_pipe_sequence.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthan <dthan@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/16 08:37:39 by dthan             #+#    #+#             */
/*   Updated: 2020/10/13 12:20:44 by dthan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	execute_pipe_sequence(t_astnode *ast, t_job *j)
{
	int		pipefd[2];

	if (ast->type == AST_pipe_sequence)
	{
		pipe(pipefd);
		j->stdout = pipefd[WRITE_END];
		execute_command(ast->left, j);
		close(j->stdout);
		job_command_builder(1, j, " | ");
		j->stdin = pipefd[READ_END];
		execute_pipe_sequence(ast->right, j);
		close(j->stdin);
	}
	else
		execute_command(ast, j);
}
