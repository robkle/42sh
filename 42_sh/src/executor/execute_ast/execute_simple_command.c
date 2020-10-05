/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_simple_command.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthan <dthan@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/16 08:39:32 by dthan             #+#    #+#             */
/*   Updated: 2020/10/05 05:46:19 by dthan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void			clear_ast(t_astnode *ast)
{
	//printBinaryTree(ast);
	if (ast->left)
		clear_ast(ast->left);
	if (ast->right)
		clear_ast(ast->right);
	ft_delast(ast);
}

void init_process(t_process *p, const t_job *j)
{
	p->av = (char**)malloc(sysconf(_SC_ARG_MAX));
	p->ac = 0;
	p->pid = 0;
	p->stdin = j->stdin;
	p->stdout = j->stdout;
	p->stderr = j->stderr;
	p->redi = NULL;
	p->completed = 0;
	p->stopped = 0;
	p->status = 0;
}

int				execute_simple_command(t_astnode *ast, t_list **heredoc, t_job *job)
{
	int status;
	t_list *node;
	t_process process;

	status = 1; //need to look at this variable!!!
	init_process(&process, job);
	if (ast->type == AST_simple_command)
	{
		execute_cmd_name(ast->left, job, &process);
		execute_cmd_suffix(ast->right, heredoc, job, &process);
	}
	else
		execute_cmd_name(ast, job, &process);
	lauch_process(job, &process); // no need to pass address, change later
	//need to delete process (only save if it run background)
	node = ft_lstnew(&process, sizeof(t_process));
	if (job->process == NULL)
		job->process = node;
	else
		ft_lstadd_tail(&job->process, node);
	return (status);
}
