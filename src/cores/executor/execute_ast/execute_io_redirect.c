/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_io_redirect.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthan <dthan@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/01 06:04:12 by dthan             #+#    #+#             */
/*   Updated: 2020/12/18 18:16:00 by dthan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void put_to_redi_list(t_redi *new_redi, t_redi **first_redi)
{
	t_redi *redi_ptr;
	
	if (*first_redi == NULL)
		*first_redi = new_redi;
	else
	{
		redi_ptr = *first_redi;
		while (redi_ptr->next)
			redi_ptr = redi_ptr->next;
		redi_ptr->next = new_redi;
	}
}

t_redi	*create_redi(void)
{
	t_redi *redi;

	redi = ft_memalloc(sizeof(t_redi));
	redi->op = NULL;
	redi->n = NULL;
	redi->word = NULL;
	return (redi);
}

void execute_io_file(t_astnode *ast, t_job *j, t_redi *redi)
{
	redi->op = ft_strdup(ast->data);
	redi->word = ft_strdup(ast->left->data);
	job_command_builder(3, j, redi->op, " ", redi->word);
}

void execute_io_here(t_astnode *ast, t_job *j, t_redi *redi)
{
	redi->op = ft_strdup(ast->data);
	if (g_shell.first_heredoc->doc)
		redi->word = ft_strdup(g_shell.first_heredoc->doc);
	job_command_builder(3, j, redi->op, " ", ast->left->data);
	g_shell.first_heredoc = g_shell.first_heredoc->next;
}

void	execute_io_redirect(t_astnode *ast, t_job *j, t_process *p)
{
	t_redi	*redi;

	redi = create_redi();
	if (ast->type == AST_io_redirect)
	{
		redi->n = ft_strdup(ast->data);
		job_command_builder(2, j, " ", redi->n);
		if (ast->left->type == AST_io_file)
			execute_io_file(ast->left, j, redi);
		else if (ast->left->type == AST_io_here)
			execute_io_here(ast->left, j, redi);
	}
	else
	{
		job_command_builder(1, j, " ");
		if (ast->type == AST_io_file)
			execute_io_file(ast, j, redi);
		else if (ast->type == AST_io_here)
			execute_io_here(ast, j, redi);
	}
	put_to_redi_list(redi, &p->first_redi);
}
