/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_complete_command.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthan <dthan@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/16 08:30:58 by dthan             #+#    #+#             */
/*   Updated: 2020/10/01 05:57:16 by dthan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	execute_complete_command(t_astnode *ast, t_list **heredoc)
{
	t_job *job;

	job = create_job();		
	if (ast->type == AST_complete_command)
	{
		if (ft_strequ(ast->data, "&"))
			job->foreground = 0;
		execute_list(ast->left, heredoc, job);
	}
	else
		execute_list(ast, heredoc, job);
}
