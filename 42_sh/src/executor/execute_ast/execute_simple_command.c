/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_simple_command.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthan <dthan@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/16 08:39:32 by dthan             #+#    #+#             */
/*   Updated: 2020/10/06 19:13:26 by dthan            ###   ########.fr       */
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

void	execute_simple_command(t_astnode *ast, t_list **heredoc, t_job *j)
{
	t_list	*p_ptr;
	t_process *p;

	p_ptr = create_process(j);
	p = (t_process*)(p_ptr->content);
	if (ast->type == AST_simple_command)
	{
		execute_cmd_name(ast->left, j, p);
		execute_cmd_suffix(ast->right, heredoc, j, p);
	}
	else
		execute_cmd_name(ast, j, p);
	p->status = lauch_process(j, p);
	put_to_plist(p_ptr, &j->first_process);
}
