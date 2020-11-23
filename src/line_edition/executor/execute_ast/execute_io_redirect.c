/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_io_redirect.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthan <dthan@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/01 06:04:12 by dthan             #+#    #+#             */
/*   Updated: 2020/10/27 16:28:18 by dthan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void execute_io_file(t_astnode *ast, t_redi *redi)
{
	redi->op = ast->data;
	redi->word = ast->left->data;
}

void execute_io_here(t_astnode *ast, t_redi *redi)
{
	redi->op = ast->data;
	redi->word = (char*)(g_shell.heredoc)->content;
	g_shell.heredoc = g_shell.heredoc->next;
}

void	execute_io_redirect(t_astnode *ast, t_process *p)
{
	t_redi	redi;
	t_list	*node;

	redi.op = NULL;
	redi.n = NULL;
	redi.word = NULL;
	if (ast->type == AST_io_redirect)
	{
		redi.n = ast->data;
		if (ast->left->type == AST_io_file)
			execute_io_file(ast->left, &redi);
		else if (ast->left->type == AST_io_here)
			execute_io_here(ast->left, &redi);
	}
	else
	{
		if (ast->type == AST_io_file)
			execute_io_file(ast, &redi);
		else if (ast->type == AST_io_here)
			execute_io_here(ast, &redi);
	}
	node = ft_lstnew(&redi, sizeof(t_redi));
	if (p->redi == NULL)
		p->redi = node;
	else
		ft_lstadd_tail(&(p->redi), node);
}
