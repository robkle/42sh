/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_pipe_sequence.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthan <dthan@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/16 08:37:39 by dthan             #+#    #+#             */
/*   Updated: 2020/10/06 17:19:38 by dthan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

t_list	*create_process(t_job *j)
{
	t_process process;
	t_list		*node;

	process.av = (char**)ft_memalloc(sysconf(_SC_ARG_MAX));
	process.ac = 0;
	process.pid = 0;
	process.stdin = j->stdin;
	process.stdout = j->stdout;
	process.stderr = j->stderr;
	process.redi = NULL;
	process.completed = NOT_COMPLETED;
	process.stopped = NOT_STOPPED;
	process.status = UNAVAILABLE_STATUS;
	node = ft_lstnew(&process, sizeof(t_process));
	return (node);
}

void put_to_plist(t_list *new_process, t_list **first_process)
{
	if (*first_process == NULL)
		*first_process = new_process;
	else
		ft_lstadd(first_process, new_process);
}

void	execute_pipe_sequence(t_astnode *ast, t_list **heredoc, t_job *j)
{
	int		pipefd[2];
	t_list	*p;

	p = create_process(j);
	if (ast->type == AST_pipe_sequence)
	{
		pipe(pipefd);
		j->stdout = pipefd[WRITE_END];
		execute_command(ast->left, heredoc, j, (t_process*)(p->content));
		close(j->stdout);
		put_to_plist(p, &j->first_process);
		j->stdin = pipefd[READ_END];
		execute_pipe_sequence(ast->right, heredoc, j);
		close(j->stdin);
	}
	else
	{
		execute_command(ast, heredoc, j, (t_process*)(p->content));
		put_to_plist(p, &j->first_process);
	}
}
