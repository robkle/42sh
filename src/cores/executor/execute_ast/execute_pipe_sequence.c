/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_pipe_sequence.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthan <dthan@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/16 08:37:39 by dthan             #+#    #+#             */
/*   Updated: 2021/02/17 01:05:43 by dthan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

/*
** Do not change order of the pipe since it will make a lot of problems
**	such as, sigpipe or waitpid stucks
*/

// void	execute_pipe_sequence(t_astnode *ast, t_job *j)
// {
// 	int		pipefd[2];

// 	j->stdout = STDOUT_FILENO;
// 	if (ast->type == AST_pipe_sequence)
// 	{
// 		pipe(pipefd);
// 		j->stdout = pipefd[WRITE_END];
// 		if (j->pipe_fd_closer[0] == 0)
// 			j->pipe_fd_closer[0] = pipefd[READ_END];
// 		else
// 			j->pipe_fd_closer[1] = pipefd[READ_END];
// 		execute_command(ast->left, j);
// 		j->pipe_fd_closer[0] = 0;
// 		j->pipe_fd_closer[1] = 0;
// 		job_command_builder(1, j, " | ");
// 		j->stdin = pipefd[READ_END];
// 		j->pipe_fd_closer[0] = pipefd[WRITE_END];
// 		close(pipefd[WRITE_END]);
// 		execute_pipe_sequence(ast->right, j);
// 		close(pipefd[READ_END]);
// 	}
// 	else
// 		execute_command(ast, j);
// }

void	execute_pipe_sequence(t_astnode *ast, t_job *j)
{
	int		pipefd[2];
	int		saved[2];

	j->stdout = STDOUT_FILENO;
	if (ast->type == AST_pipe_sequence)
	{
		// saved the stdint and out so that we can reset
		saved[0] = j->stdin;
		saved[1] = j->stdout;
		// start piping
		pipe(pipefd);
		// stdout -> pipe write end
		j->stdout = pipefd[WRITE_END];
		// init pipe fd closer, at 0 when p1
		// if 0 already is occupied, then 1 will take the place
		if (j->pipe_fd_closer[0] == 0)
			j->pipe_fd_closer[0] = pipefd[READ_END];
		else
			j->pipe_fd_closer[1] = pipefd[READ_END];
		// processing
		execute_command(ast->left, j);
		// close the pipe write end
		close(pipefd[WRITE_END]);
		// reset pipe fd closer
		j->pipe_fd_closer[0] = 0;
		j->pipe_fd_closer[1] = 0;
		// reset stdout
		j->stdout = saved[1];
		job_command_builder(1, j, " | ");
		// saved the stdin
		j->stdin = pipefd[READ_END];
		// pipe fd closer for write end
		j->pipe_fd_closer[0] = pipefd[WRITE_END];
		
		execute_pipe_sequence(ast->right, j);
		close(pipefd[READ_END]);
		j->stdin = saved[0];
	}
	else
		execute_command(ast, j);
}
