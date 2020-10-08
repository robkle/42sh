/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_and_or.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthan <dthan@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/16 08:35:52 by dthan             #+#    #+#             */
/*   Updated: 2020/10/08 02:43:48 by dthan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int last_process_status(t_job *job)
{
	t_list *p_ptr;
	t_process *p;

	p_ptr = job->first_process;
	while (p_ptr && p_ptr->next)
		p_ptr = p_ptr->next;
	p = (t_process*)p_ptr->content;
	return (p->status);
}

void	execute_and_or(t_astnode *ast, t_list **heredoc, t_job *job)
{
	if (ast->type == AST_and_or && ft_strequ(ast->data, "&&"))
	{
		execute_pipeline(ast->left, heredoc, job);
		if (last_process_status(job) == 0)
			execute_and_or(ast->right, heredoc, job);
		else if (ast->right->right->type == AST_and_or)
			execute_and_or(ast->right->right, heredoc, job);
	}
	else if (ast->type == AST_and_or && ft_strequ(ast->data, "||"))
	{
		execute_pipeline(ast->left, heredoc, job);
		if (last_process_status(job) != 0)
			execute_and_or(ast->right, heredoc, job);
		else if (ast->right->right->type == AST_and_or)
			execute_and_or(ast->right->right, heredoc, job);
	}
	else
		return (execute_pipeline(ast, heredoc, job));
}
