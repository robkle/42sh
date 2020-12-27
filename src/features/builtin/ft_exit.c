/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthan <dthan@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/06 15:27:24 by ihwang            #+#    #+#             */
/*   Updated: 2020/12/25 19:03:15 by dthan            ###   ########.fr       */
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

int			ft_exit(int opt)
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
	** @ delete job
	** if there is a job in the list, first update the status of all the job
	** then delete it, and sending the option 1, to unstop the stopped process
	*/
	if (g_shell.first_job)
	{
		update_status();
		delete_job(g_shell.first_job, 1);
	}
	exit(opt);
	return (EXIT_FAILURE);
}
