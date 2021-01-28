/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_and_or_bg.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthan <dthan@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/13 11:47:53 by dthan             #+#    #+#             */
/*   Updated: 2021/01/28 02:42:07 by dthan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	and_or_child(t_astnode *ast)
{
	pid_t cpid;

	cpid = getpid();
	setpgid(cpid, cpid);
	execute_and_or(ast, 0, 1, 0);
	exit(EXIT_SUCCESS);
}

void	execute_and_or_bg(t_astnode *ast)
{
	t_job		*j;
	pid_t		pid;
	t_process	*p;

	j = create_job(0, 1);
	pid = fork();
	if (pid == 0)
		and_or_child(ast);
	else if (pid < 0)
	{
		ft_dprintf(2, "Fork failed at execute_and_or_bg\n");
		ft_exit(EXIT_FAILURE);
	}
	p = create_process(j);
	p->pid = pid;
	j->pgid = pid;
	build_and_or_command(ast, j);
	setpgid(pid, pid);
	ft_printf("[%d] %d\n", j->id, j->pgid);
	put_to_list_job(j);
}
