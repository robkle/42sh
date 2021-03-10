/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_pipe_sequence_helper.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthan <dthan@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/07 16:13:30 by dthan             #+#    #+#             */
/*   Updated: 2021/03/10 20:42:31 by dthan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

/*
** Procedure:
**		1. save the stdint and out so that we can reset (line 36-37)
**		2. start piping (line 38)
**		3. stdout -> pipe write-end (line 39)
**		4. init pipe_fd_closer for pipe-readend, at 0 when p1, if 0 already is
**		   occupied, then 1 will take place (line 40-43)
**		5. processing process (line 44)
**		6. close the pipe write-end (line 45)
**		7. reset pipe_fd_closer (46-47)
**		8. reset stdout (48)
**		9. save the stdin (50)
**		10. pipe_fd_closer for write-end (51)
**		11. recusive (52)
**		12. close the pipe read-end (53)
**		13. reset stdin (54)
*/

void	execute_pipe_sequence_helper(
	int pipefd[2], int saved[2], t_astnode *ast, t_job *j)
{
	saved[0] = j->stdin;
	saved[1] = j->stdout;
	pipe(pipefd);
	j->stdout = pipefd[WRITE_END];
	if (j->pipe_fd_closer[0] == 0)
		j->pipe_fd_closer[0] = pipefd[READ_END];
	else
		j->pipe_fd_closer[1] = pipefd[READ_END];
	execute_command(ast->left, j);
	close(pipefd[WRITE_END]);
	j->pipe_fd_closer[0] = 0;
	j->pipe_fd_closer[1] = 0;
	j->stdout = saved[1];
	job_command_builder(1, j, " | ");
	j->stdin = pipefd[READ_END];
	j->pipe_fd_closer[0] = pipefd[WRITE_END];
	execute_pipe_sequence(ast->right, j);
	close(pipefd[READ_END]);
	j->stdin = saved[0];
}
