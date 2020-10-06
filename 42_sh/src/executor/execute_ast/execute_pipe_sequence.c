/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_pipe_sequence.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthan <dthan@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/16 08:37:39 by dthan             #+#    #+#             */
/*   Updated: 2020/10/06 19:10:38 by dthan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"



void	execute_pipe_sequence(t_astnode *ast, t_list **heredoc, t_job *j)
{
	int		pipefd[2];

	if (ast->type == AST_pipe_sequence)
	{
		pipe(pipefd);
		j->stdout = pipefd[WRITE_END];
		execute_command(ast->left, heredoc, j);
		close(j->stdout);
		j->stdin = pipefd[READ_END];
		execute_pipe_sequence(ast->right, heredoc, j);
		close(j->stdin);
	}
	else
	{
		execute_command(ast, heredoc, j);
	}
}
