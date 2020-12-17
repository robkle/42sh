/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_and_or_bg.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthan <dthan@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/13 11:47:53 by dthan             #+#    #+#             */
/*   Updated: 2020/10/14 13:00:20 by dthan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void build_command_name_command(t_astnode *ast, t_job *j)
{
	if (ast->type == AST_WORD)
		job_command_builder(1, j, ast->data);
}

void build_command_io_redirect_command(t_astnode *ast, t_job *j)
{
	//will take care IO token
	if (ast->left->type == AST_io_file)
	{
		job_command_builder(2, j, " ", ast->data);
		job_command_builder(2, j, " ", ast->left->data);
		job_command_builder(2, j, " ", ast->left->left->data);
	}
	else if (ast->left->type == AST_io_here)
	{
		//maybe sth here
		job_command_builder(2, j, " ", ast->left->data);
		job_command_builder(2, j, " ", ast->left->left->data);
		g_shell.heredoc = g_shell.heredoc->next;
	}
}

void build_command_suffix_command(t_astnode *ast, t_job *j)
{
	if (ast->type == AST_WORD)
		job_command_builder(2, j, " ", ast->data);
	else if (ast->type == AST_cmd_suffix)
	{
		if (ast->left->type == AST_io_redirect)
		{
			build_command_io_redirect_command(ast->left, j);
			build_command_suffix_command(ast->right, j);
		}
		else if (ast->left->type == AST_WORD)
		{
			job_command_builder(2, j, " ", ast->left->data);
			build_command_suffix_command(ast->right, j);
		}
	}
	else if (ast->type == AST_io_redirect)
		build_command_io_redirect_command(ast, j);
}

void build_simple_command_command(t_astnode *ast, t_job *j)
{
	if (ast->type == AST_simple_command)
	{
		build_command_name_command(ast->left, j);
		build_command_suffix_command(ast->right, j);
	}
	else
		build_command_name_command(ast, j);
}

void build_pipe_sequence_command(t_astnode *ast, t_job *j)
{
	if (ast->type == AST_pipe_sequence)
	{
		build_simple_command_command(ast->left, j);
		job_command_builder(1, j, " | ");
		build_pipe_sequence_command(ast->right, j);
	}
	else
		build_simple_command_command(ast, j);
}

void build_and_or_command(t_astnode *ast, t_job *j)
{
	if (ast->type == AST_and_or)
	{
		build_pipe_sequence_command(ast->left, j);
		job_command_builder(3, j, " ", ast->data, " ");
		build_and_or_command(ast->right, j);
	}
	else
		build_pipe_sequence_command(ast, j);
}

void and_or_child(t_astnode *ast)
{
	pid_t cpid;

	cpid = getpid();
	setpgid(cpid, cpid);
	execute_and_or(ast, 0, 1, 0);
	exit(EXIT_SUCCESS);
}

void	execute_and_or_bg(t_astnode *ast)
{
	t_job *j;
	pid_t pid;
	t_process *p;

	j = create_job(0, 1);
	pid = fork();
	if (pid == 0)
		and_or_child(ast);
	else if (pid < 0)
	{
		perror("fork"); //error management here
		ft_exit(EXIT_FAILURE);
	}
	p = create_process(j);
	p->pid = pid;
	j->pgid = pid;
	build_and_or_command(ast, j);
	setpgid(pid, pid);
	ft_printf("[%d] %d\n", j->id, j->pgid);
}
