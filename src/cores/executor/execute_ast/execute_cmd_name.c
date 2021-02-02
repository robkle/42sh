/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmd_name.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthan <dthan@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/17 10:50:56 by dthan             #+#    #+#             */
/*   Updated: 2021/01/28 13:16:32 by dthan            ###   ########.fr       */
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

/* old
void	execute_cmd_name(t_astnode *ast, t_job *j, t_process *p)
{
	if (ast->type == AST_WORD)
	{
		p->ac = 1;
		p->av[0] = (char*)ft_memalloc(sizeof(char) * sysconf(_SC_ARG_MAX));
		ft_memcpy(p->av[0], ast->data, ft_strlen(ast->data));
		p->av[1] = NULL;
		job_command_builder(1, j, p->av[0]);
	}
}
*/
