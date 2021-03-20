/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihwang <ihwang@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/06 15:27:24 by ihwang            #+#    #+#             */
/*   Updated: 2021/03/20 03:09:16 by ihwang           ###   ########.fr       */
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

int			ft_exit_internal(int ret_value)
{
	/*
	** history part
	*/
	append_history();
	delete_save_history();
	ft_arraydel(g_shell.history->hist);
	free(g_shell.history->tmp);
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
	** delete aliastable
	*/
	remove_all(&g_shell.alias);
	/*
	** delete hashtable
	*/
	remove_hashentries();
	/*
	** delete builtin commands list
	*/
	delete_builtin_commands();
	
	ft_dprintf(STDERR_FILENO, "exit\n");
	exit(ret_value);
	return (EXIT_FAILURE);
}

int			ft_exit(t_process *p)
{
	char	ret_value;
	char	is_longlong;

	if (p->av[1] != NULL)
	{
		if (is_made_of_digits(p->av[1]))
		{
			ret_value = (char)ft_atolli_check(p->av[1], &is_longlong);
			if (is_longlong && p->ac > 2)
				ft_dprintf(STDERR_FILENO, "%s: exit: too many arguments\n", SHELL_NAME);
			if (is_longlong)
				ft_exit_internal(ret_value);
			if (!is_longlong)
			{
				ft_dprintf(STDERR_FILENO, "%s: exit: %s: numeric argument required\n", SHELL_NAME, p->av[1]);
				return (EXIT_FAILURE);
			}
		}
		else
		{
			ft_dprintf(STDERR_FILENO, "%s: exit: %s: numeric argument required\n", SHELL_NAME, p->av[1]);
			return (EXIT_FAILURE);
		}
	}
	return (ft_exit_internal(g_shell.exit_status));
}
