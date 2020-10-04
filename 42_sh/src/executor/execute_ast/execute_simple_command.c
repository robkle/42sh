/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_simple_command.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthan <dthan@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/16 08:39:32 by dthan             #+#    #+#             */
/*   Updated: 2020/10/02 17:04:13 by dthan            ###   ########.fr       */
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

void init_process(t_process *p, t_job *j)
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

void print_process(t_process p)
{
	ft_printf("=============\nprocess info:\nac: %d\nav[0]: %s\npid: %d\nstdin: %d\nstdout: %d\nstderr: %d\n==================\n", p.ac, p.av[0], p.pid, p.stdin, p.stdout, p.stderr);
}

void print_redirect(t_process p)
{
	t_list *ptr;
	t_redirect	*redi;
	
	ft_printf("=======redirect info========\n");
	ptr = p.redi;
	while(ptr)
	{
		redi = ptr->content;
		ft_printf("redirect_op: %s\nredirect_src: %s\nredirect_des: %s\n", redi->redirect_op, redi->redirect_src, redi->redirect_des);
		if (ptr->next != NULL)
			ft_printf("===> NEXT\n");
		ptr = ptr->next;
	}
	ft_printf("============================\n");
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
	// print_process(process);
	// print_redirect(process);
	lauch_process(job, &process); // no need to pass address, change later
	//need to delete process (only save if it run background)
	node = ft_lstnew(&process, sizeof(t_process));
	if (job->process == NULL)
		job->process = node;
	else
		ft_lstadd_tail(&(job->process), node);
	return (status);
}
