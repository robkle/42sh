/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmd_name.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthan <dthan@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/17 10:50:56 by dthan             #+#    #+#             */
/*   Updated: 2020/10/05 15:17:49 by dthan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	execute_cmd_name(t_astnode *ast, t_job *j, t_process *p)
{
	if (ast->type == AST_WORD)
	{
		p->ac = 1;
		p->av[0] = ast->data;
		p->av[1] = NULL;
		if (j->command != NULL)
		{
			j->command = ft_strjoin_and_free_string1(j->command, " |");
			j->command = ft_strjoin_and_free_string1(j->command, p->av[0]);
		}
		else
			j->command = ft_strdup(p->av[0]);
	}
}
