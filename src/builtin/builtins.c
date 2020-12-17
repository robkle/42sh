/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthan <dthan@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/06 15:27:24 by ihwang            #+#    #+#             */
/*   Updated: 2020/10/14 13:49:11 by dthan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int			ft_env(void)
{
	int		i;

	i = -1;
	while (g_env[++i])
	{
		ft_putstr(g_env[i]);
		ft_putstr("\n");
	}
	return (EXIT_SUCCESS);
}

int			ft_pwd()
{
	char	pwd[PATH_MAX];

	if ((getcwd(pwd, PATH_MAX)) == NULL)
		return (EXIT_FAILURE);
	ft_putstr(pwd);
	ft_putstr("\n");
	return (EXIT_SUCCESS);
}

int			ft_exit(int opt)
{
	int		i;

	i = -1;
	append_history();//NEW
	delete_save_history();
	ft_arraydel(g_h->hist);//NEW
	free(g_h->hist);//NEW
	free(g_h);//NEW	
	while (g_env[++i])
		ft_strdel(&g_env[i]);
	ft_strdel(&g_env[i]);
	free(g_env);
	/* delete job*/
	t_job *j_ptr;

	update_status();
	i = 0;
	while (g_shell.first_job->next)
	{
		j_ptr = (t_job*)(g_shell.first_job->content);
		if (job_is_stopped(j_ptr))
		{
			if (kill(- j_ptr->pgid, SIGCONT) < 0)
				perror("kill (SIGCONT)");
		}
		kill(- j_ptr->pgid, SIGTERM);
		delete_job(g_shell.first_job);
		g_shell.first_job = g_shell.first_job->next;
	}
	delete_job(g_shell.first_job);
	exit(opt);
	return (EXIT_FAILURE);
}

int			ft_echo(t_process *p)
{
	int		i;

	i = 0;
	while (++i < p->ac)
	{
		ft_putstr(p->av[i]);
		if (i + 1 != p->ac && ft_strcmp(p->av[i], ""))
			ft_putstr(" ");
	}
	ft_putchar('\n');
	return (EXIT_SUCCESS);
}
