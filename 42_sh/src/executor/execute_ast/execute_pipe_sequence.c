/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_pipe_sequence.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthan <dthan@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/16 08:37:39 by dthan             #+#    #+#             */
/*   Updated: 2020/10/01 05:57:44 by dthan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

// static void	execute_pipe_left(t_astnode *ast,
// t_exe *exec, pid_t pid[2], int pipefd[2])
// {
// 	pipe(pipefd);
// 	pid[0] = fork();
// 	if (pid[0] == 0)
// 	{
// 		close(pipefd[READ_END]);
// 		dup2(pipefd[WRITE_END], STDOUT_FILENO);
// 		execute_command(ast->left, exec);
// 		dup2(STDOUT_FILENO, pipefd[WRITE_END]);
// 		exit(EXIT_SUCCESS);
// 	}
// }

// static void	execute_pipe_right(t_astnode *ast,
// t_exe *exec, pid_t pid[2], int pipefd[2])
// {
// 	pid[1] = fork();
// 	if (pid[1] == 0)
// 	{
// 		close(pipefd[WRITE_END]);
// 		dup2(pipefd[READ_END], STDIN_FILENO);
// 		execute_pipe_sequence(ast->right, exec);
// 		dup2(STDIN_FILENO, pipefd[READ_END]);
// 		exit(EXIT_SUCCESS);
// 	}
// }

// static void	init_job(void)
// {
// 	t_job	job;
// 	t_list	*new_node;

// 	job.pgid = 0;
// 	//should be set in child process
// 	job.command = NULL;
// 	//in execute_simple_command 
// 	job.notified = 0;
// 	tcgetattr(STDIN_FILENO, &job.term);
// 	new_node = ft_lstnew(&job, sizeof(t_job));
// 	if (g_shell.job)
// 		g_shell.job = new_node;
// 	else
// 		ft_lstadd(&g_shell.job, new_node);
// }

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

// int			execute_pipe_sequence(t_astnode *ast, t_exe *exec)
// {
// 	int		pipefd[2];
// 	int		status;
// 	pid_t	pid[2];

// 	init_job();
// 	if (ast->type == AST_pipe_sequence)
// 	{
// 		execute_pipe_left(ast, exec, pid, pipefd);
// 		execute_pipe_right(ast, exec, pid, pipefd);
// 		close(pipefd[0]);
// 		close(pipefd[1]);
// 		waitpid(pid[0], &status, 0);
// 		waitpid(pid[1], &status, 0);
// 	}
// 	else
// 		status = execute_command(ast, exec);
// 	return (status);
// }

// void wait_for_job(pid_t pid)
// {
// 	waitpid(pid, NULL, WUNTRACED);
// }

// void put_job_in_foreground(t_job *job, t_process *process)
// {
// 	//put job in foreground
// 	tcsetpgrp(STDIN_FILENO, job->pgid);
// 	/* send the signal ?? */
// 	//wait for it to report
// 	wait_for_job(process->pid);
// 	//put the shell back in the foreground
// 	tcsetpgrp(STDIN_FILENO, g_shell.shell_pgid);
// 	//restore the shell's terminal modes
// 	tcgetattr(STDIN_FILENO, &job->term);
// 	tcsetattr(STDIN_FILENO, TCSADRAIN, &g_shell.shell_tmode);
// }

// void lauch_process(t_process *process, pid_t pgid, int infile, int outfile, int errfile, in foreground)
// {
// 	pid_t pid;
// 	pid = getpid();
// 	if (pgid == 0)
// 	pgid = pid;
// 	setpgid(pid, pgid);
// 	if (foreground)
// 		tcsetpgrp(STDIN_FILENO, pgid); //change our own function later
// 	/* Set the handling for job control */
// 	signal(SIGINT, SIG_DFL);
// 	signal(SIGQUIT, SIG_DFL);
// 	signal(SIGTSTP, SIG_DFL);
// 	signal(SIGTTIN, SIG_DFL);
// 	signal(SIGTTOU, SIG_DFL);
// 	signal(SIGCHLD, SIG_DFL);

// 	/* Set the standard input /ouput channels of the new process */
// 	if (infile != STDIN_FILENO)
// 	{
// 		dup2(infile, STDIN_FILENO);
// 		close(infile);
// 	}
// 	if (outfile != STDOUT_FILENO)
// 	{
// 		dup2(outfile, STDOUT_FILENO);
// 		close(outfile);
// 	}
// 	if (errfile != STDERR_FILENO)
// 	{
// 		dup2(errfile, STDERR_FILENO);
// 		close(errfile);
// 	}
// 	execute_command(ast->left, exec);
// 	exit(EXIT_SUCCESS);
// }

// int			execute_pipe_sequence(t_astnode *ast, t_exe *exec, t_job *job)
// {
// 	int		pipefd[2];
// 	int		status;
// 	pid_t	pid;
// 	t_process *process;
// 	int infile, outfile, errfile;
// 	pid_t	cpid;

// 	infile = job->stdin; //infile
// 	errfile = job->stderr; //errfile
// 	if (ast->type == AST_pipe_sequence)
// 	{
// 		pipe(pipefd);
// 		outfile = pipefd[WRITE_END]; //outfile
// 		pid = fork();
// 		if (pid == 0)
// 			lauch_process(process, job->pgid, infile, outfile, job->stderr, job->foreground);
// 		else if (pid < 0)
// 		{
// 			perror("fork"); // change perror later
// 			exit(EXIT_FAILURE);
// 		}
// 		else
// 		{
// 			process->pid = pid;
// 			if (job->pgid == 0)
// 				job->pgid = pid;
// 			setpgid(pid, job->pgid);
// 		}
// 		// clean up after pipes
// 		if (infile != job->stdin) //need to check here, do i need to?
// 			close(infile);
// 		if (outfile != job->stdout)
// 			close(outfile);
// 		infile = pipefd[READ_END];

// 		if (job->foreground)
// 			put_job_in_foreground(job, process);
// 	}
// 	else
// 		status = execute_command(ast, exec);
// 	return (status);
// }
