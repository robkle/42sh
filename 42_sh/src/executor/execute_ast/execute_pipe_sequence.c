/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_pipe_sequence.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthan <dthan@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/16 08:37:39 by dthan             #+#    #+#             */
/*   Updated: 2020/10/05 05:43:14 by dthan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int			execute_pipe_sequence(t_astnode *ast, t_list **heredoc, t_job *job)
{
	int		pipefd[2];
	int		status;

	if (ast->type == AST_pipe_sequence)
	{
		pipe(pipefd);
		job->stdout = pipefd[WRITE_END];
		execute_command(ast->left, heredoc, job);
		close(job->stdout);
		job->stdin = pipefd[READ_END];
		execute_pipe_sequence(ast->right, heredoc, job);
		close(job->stdin);
	}
	else
		status = execute_command(ast, heredoc, job);
	return (status);
}
