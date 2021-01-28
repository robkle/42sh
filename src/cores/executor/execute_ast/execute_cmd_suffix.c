/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmd_suffix.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthan <dthan@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/17 11:14:52 by dthan             #+#    #+#             */
/*   Updated: 2021/01/28 02:46:36 by dthan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	execute_cmd_suffix(t_astnode *ast, t_job *j, t_process *p)
{
	if (ast->type == AST_cmd_suffix)
	{
		if (ast->left->type == AST_WORD)
		{
			p->ac++;
			p->av[p->ac - 1] = ft_strdup(ast->left->data);
			p->av[p->ac] = NULL;
			job_command_builder(2, j, " ", p->av[p->ac - 1]);
		}
		else
			execute_io_redirect(ast->left, j, p);
		execute_cmd_suffix(ast->right, j, p);
	}
	else if (ast->type == AST_WORD)
	{
		p->ac++;
		p->av[p->ac - 1] = ft_strdup(ast->data);
		p->av[p->ac] = NULL;
		job_command_builder(2, j, " ", p->av[p->ac - 1]);
	}
	else
		execute_io_redirect(ast, j, p);
}

/*
** old
void	execute_cmd_suffix(t_astnode *ast, t_job *j, t_process *p)
{
	if (ast->type == AST_cmd_suffix)
	{
		if (ast->left->type == AST_WORD)
		{
			if (p->ac > MAX_ARGV)
			{
				ft_dprintf(2, "Error: Passing max argv value");
				exit(-1);
			}
			p->ac++;
			p->av[p->ac - 1] = (char*)ft_memalloc(sizeof(char) * sysconf(_SC_ARG_MAX));
			ft_memcpy(p->av[p->ac - 1], ast->left->data, ft_strlen(ast->left->data));
			p->av[p->ac] = NULL;
			job_command_builder(2, j, " ", p->av[p->ac - 1]);
		}
		else
			execute_io_redirect(ast->left , j, p);
		execute_cmd_suffix(ast->right, j, p);
	}
	else if (ast->type == AST_WORD)
	{
		if (p->ac > MAX_ARGV)
		{
			ft_dprintf(2, "Error: Passing max argv value");
			exit(-1);
		}
		p->ac++;
		p->av[p->ac - 1] = (char*)ft_memalloc(sizeof(char) * sysconf(_SC_ARG_MAX));
		ft_memcpy(p->av[p->ac - 1], ast->data, ft_strlen(ast->data));
		p->av[p->ac] = NULL;
		job_command_builder(2, j, " ", p->av[p->ac - 1]);
	}
	else
		execute_io_redirect(ast, j, p);
}
*/
