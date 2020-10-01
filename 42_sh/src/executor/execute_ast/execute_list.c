/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_list.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthan <dthan@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/16 08:35:21 by dthan             #+#    #+#             */
/*   Updated: 2020/10/01 05:57:20 by dthan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

/*
void	open_iofile(t_astnode *ast, char *redirect_op)
{
	int fd;

	if (ast->type == AST_io_file && (ft_strequ(">", ast->data) || \
		ft_strequ(">&", ast->data) || ft_strequ(">>", ast->data)))
		open_iofile(ast->left, ast->data);
	else if (ast->type == AST_WORD)
	{
		if (!(ft_strequ(redirect_op, ">&") && (ft_strequ(ast->data, "-") || \
			is_made_of_digits(ast->data))))
		{
			fd = open(ast->data, O_CREAT, 0644);
			close(fd);
		}
	}
}

void	find_iofile(t_astnode *ast)
{
	if (ast->type == AST_io_redirect)
		open_iofile(ast->right, NULL);
	else if (ast->type == AST_pipe_sequence)
	{
		find_iofile(ast->left);
		find_iofile(ast->right);
	}
	else if (ast->type == AST_simple_command)
		find_iofile(ast->right);
	else if (ast->type == AST_cmd_suffix)
	{
		find_iofile(ast->left);
		find_iofile(ast->right);
	}
}
*/

void put_job_in_foreground(t_job *job)
{
	/* put the job into the foreground */
	tcsetpgrp(STDIN_FILENO, job->pgid);
	/* wait for it to report */
	// wait_for_job(job); not sure abt this
	waitpid(job->pgid, NULL, WUNTRACED);
	// put the shell back in the foreground
	tcsetpgrp(STDIN_FILENO, g_shell.shell_pgid);

	/* Restore the shell's terminal modes*/
	tcgetattr(STDIN_FILENO, &job->term);
	tcsetattr(STDIN_FILENO, TCSADRAIN, &g_shell.shell_tmode);
}

void	execute_list(t_astnode *ast, t_list **heredoc, t_job *first_job)
{
	t_job *next_job;

	next_job = NULL;
	if (ast->type == AST_list)
	{
		//find_iofile(ast->left);
		next_job = create_job();
		if (ft_strequ(ast->data, "&"))
			next_job->foreground = 0;
		execute_and_or(ast->left, heredoc, first_job);
		if (first_job->foreground)
			put_job_in_foreground(first_job);
		execute_list(ast->right, heredoc, next_job);
		if (next_job->foreground)
			put_job_in_foreground(next_job);
	}
	else
	{
		//find_iofile(ast);
		execute_and_or(ast, heredoc, first_job);
		if (first_job->foreground)
			put_job_in_foreground(first_job);
	}
}
