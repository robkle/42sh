/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_pipe_sequence.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthan <dthan@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/16 08:37:39 by dthan             #+#    #+#             */
/*   Updated: 2021/03/07 16:22:09 by dthan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

/*
** Procedure:
**	case 1: AST_pipe_sequence
**	case 2: not AST_pipe_sequence
**	NOTE: doing recursively is not recommended, due to the project has been
**		built with the recursive tree, so this way for dealing with pipe is
**		just a temporary fix
**		Do not change order of the pipe since it will make a lot of problems
**		such as, sigpipe or waitpid stucks
*/

void	execute_pipe_sequence(t_astnode *ast, t_job *j)
{
	int		pipefd[2];
	int		saved[2];

	j->stdout = STDOUT_FILENO;
	if (ast->type == AST_pipe_sequence)
		execute_pipe_sequence_helper(pipefd, saved, ast, j);
	else
		execute_command(ast, j);
}
