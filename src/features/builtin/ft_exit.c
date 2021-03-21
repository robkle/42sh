/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihwang <ihwang@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/06 15:27:24 by ihwang            #+#    #+#             */
/*   Updated: 2021/03/21 11:24:21 by ihwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

/*
** @ delete enviroment
** delete the existing enviroment
*/

static void	delete_enviroment(char **env)
{
	int i;

	i = -1;
	while (env[++i])
		ft_strdel(&env[i]);
	free(env);
}

int			ft_exit_internal(int ret_value)
{
	append_history();
	delete_save_history();
	ft_arraydel(g_shell.history->hist);
	free(g_shell.history->tmp);
	free(g_shell.history);
	delete_enviroment(g_shell.env);
	clean_table_intern_var(g_shell.intern_var);
	if (g_shell.first_job)
	{
		update_status();
		delete_job(g_shell.first_job, 1);
	}
	remove_all(&g_shell.alias);
	remove_hashentries();
	delete_builtin_commands();
	ft_dprintf(STDERR_FILENO, "exit\n");
	exit(ret_value);
	return (EXIT_FAILURE);
}

static int	numeric_arguemtn_error(char *arg)
{
	ft_dprintf(STDERR_FILENO, "%s: exit: %s: numeric argument required\n", \
	SHELL_NAME, arg);
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
				ft_dprintf(STDERR_FILENO, "%s: exit: too many arguments\n", \
				SHELL_NAME);
			if (is_longlong)
				ft_exit_internal(ret_value);
			if (!is_longlong)
				return (numeric_arguemtn_error(p->av[1]));
		}
		else
			return (numeric_arguemtn_error(p->av[1]));
	}
	return (ft_exit_internal(g_shell.exit_status));
}
