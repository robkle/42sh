/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmd_name.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthan <dthan@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/17 10:50:56 by dthan             #+#    #+#             */
/*   Updated: 2021/03/07 16:11:30 by dthan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	execute_cmd_name(t_astnode *ast, t_job *j, t_process *p)
{
	if (ast->type == AST_WORD)
	{
		p->ac = 1;
		p->av[0] = ft_strdup(ast->data);
		p->av[1] = NULL;
		job_command_builder(1, j, p->av[0]);
	}
}
