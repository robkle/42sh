/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmd_suffix.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthan <dthan@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/17 11:14:52 by dthan             #+#    #+#             */
/*   Updated: 2020/10/05 05:45:24 by dthan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	execute_cmd_suffix(t_astnode *ast, t_list **hd, t_job *j, t_process *p)
{
	if (ast->type == AST_WORD)
	{
		p->ac++;
		p->av[p->ac - 1] = ast->data;
		p->av[p->ac] = NULL;
		j->command = ft_strjoin_and_free_string1(j->command, " ");
		j->command = ft_strjoin_and_free_string1(j->command, p->av[p->ac - 1]);
	}
	else if (ast->type == AST_cmd_suffix)
	{
		if (ast->left->type == AST_io_redirect)
		{
			execute_io_redirect(ast->left, hd, p);
			execute_cmd_suffix(ast->right, hd, j, p);
		}
		else if (ast->left->type == AST_WORD)
		{
			p->ac++;
			p->av[p->ac - 1] = ast->left->data;
			p->av[p->ac] = NULL;
			// this part get job command, will move to somewhere else
			ft_strjoin_and_free_string1(j->command, " ");
			ft_strjoin_and_free_string1(j->command, p->av[p->ac - 1]);
			execute_cmd_suffix(ast->right, hd, j, p);
		}
	}
	else if (ast->type == AST_io_redirect)
		execute_io_redirect(ast, hd, p);
}
