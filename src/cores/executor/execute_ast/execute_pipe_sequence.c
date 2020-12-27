/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_pipe_sequence.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthan <dthan@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/16 08:37:39 by dthan             #+#    #+#             */
/*   Updated: 2020/12/18 18:16:22 by dthan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

/*
** Do not change order of the pipe since it will make a lot of problems
**	such as, sigpipe or waitpid stucks
*/

void	execute_pipe_sequence(t_astnode *ast, t_job *j)
{
	int		pipefd[2];

	j->stdout = STDOUT_FILENO;
	if (ast->type == AST_pipe_sequence)
	{
		pipe(pipefd);
		j->stdout = pipefd[WRITE_END];
		if (j->pipe_fd_closer[0] == 0)
			j->pipe_fd_closer[0] = pipefd[READ_END];
		else
			j->pipe_fd_closer[1] = pipefd[READ_END];
		execute_command(ast->left, j);
		j->pipe_fd_closer[0] = 0;
		j->pipe_fd_closer[1] = 0;
		job_command_builder(1, j, " | ");
		j->stdin = pipefd[READ_END];
		j->pipe_fd_closer[0] = pipefd[WRITE_END];
		close(pipefd[WRITE_END]);
		execute_pipe_sequence(ast->right, j);
		close(pipefd[READ_END]);
	}
	else
		execute_command(ast, j);
}
