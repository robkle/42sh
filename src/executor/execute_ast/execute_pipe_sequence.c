/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_pipe_sequence.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihwang <ihwang@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/16 08:37:39 by dthan             #+#    #+#             */
/*   Updated: 2020/09/23 00:40:49 by ihwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static void	execute_pipe_left(t_astnode *ast,\
t_exe *exec, pid_t pid[2], int pipefd[2])
{
	pipe(pipefd);
	pid[0] = fork();
	if (pid[0] == 0)
	{
		close(pipefd[READ_END]);
		dup2(pipefd[WRITE_END], STDOUT_FILENO);
		execute_command(ast->left, exec);
		dup2(STDOUT_FILENO, pipefd[WRITE_END]);
		exit(EXIT_SUCCESS);
	}
}

static void	execute_pipe_right(t_astnode *ast,\
t_exe *exec, pid_t pid[2], int pipefd[2])
{
	pid[1] = fork();
	if (pid[1] == 0)
	{
		close(pipefd[WRITE_END]);
		dup2(pipefd[READ_END], STDIN_FILENO);
		execute_pipe_sequence(ast->right, exec);
		dup2(STDIN_FILENO, pipefd[READ_END]);
		exit(EXIT_SUCCESS);
	}
}

static void	init_job(void)
{
	t_job	job;
	t_list	*new_node;

	job.pgid = 0;
	//should be set in child process
	job.command = NULL;
	//in execute_simple_command 
	job.notified = 0;
	tcgetattr(STDIN_FILENO, &job.term);
	new_node = ft_lstnew(&job, sizeof(t_job));
	if (g_shell.job)
		g_shell.job = new_node;
	else
		ft_lstadd(&g_shell.job, new_node);
}

int			execute_pipe_sequence(t_astnode *ast, t_exe *exec)
{
	int		pipefd[2];
	int		status;
	pid_t	pid[2];

	init_job();
	if (ast->type == AST_pipe_sequence)
	{
		execute_pipe_left(ast, exec, pid, pipefd);
		execute_pipe_right(ast, exec, pid, pipefd);
		close(pipefd[0]);
		close(pipefd[1]);
		waitpid(pid[0], &status, 0);
		waitpid(pid[1], &status, 0);
	}
	else
		status = execute_command(ast, exec);
	return (status);
}
