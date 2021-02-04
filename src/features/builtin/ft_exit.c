/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihwang <ihwang@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/06 15:27:24 by ihwang            #+#    #+#             */
/*   Updated: 2021/02/04 20:00:34 by ihwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

/*
** @ delete enviroment
** delete the existing enviroment
*/
static void delete_enviroment(char **env) {
	int i;

	i = -1;
	while (env[++i])
		ft_strdel(&env[i]);
	free(env);
}
int			ft_exit_internal(int opt)
{
	/*
	** history part
	*/
	append_history();
	delete_save_history();
	ft_arraydel(g_shell.history->hist);
	free(g_shell.history);
	/*
	** delete enviroment
	*/
	delete_enviroment(g_shell.env);
	/*
	** delete intern var
	*/
	clean_table_intern_var(g_shell.intern_var);
	/*
	** @ delete job
	** if there is a job in the list, first update the status of all the job
	** then delete it, and sending the option 1, to unstop the stopped process
	*/
	if (g_shell.first_job)
	{
		update_status();
		delete_job(g_shell.first_job, 1);
	}
	/*
	** delete hashtable
	*/
	remove_hashentries();
	/*
	** delete builtin commands list
	*/
	delete_builtin_commands();
	
	exit(opt);
	return (EXIT_FAILURE);
}

int			ft_exit(t_process *p)
{
	if (p->ac > 1)
		return (ft_exit_internal(ft_atoi(p->av[1])));
	return (ft_exit_internal(g_shell.exit_status));
}
