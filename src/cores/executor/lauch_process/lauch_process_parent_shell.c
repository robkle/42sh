/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lauch_process_parent_shell.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthan <dthan@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/28 03:49:44 by dthan             #+#    #+#             */
/*   Updated: 2021/02/15 23:50:20 by dthan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static int	lauch_process_which_can_change_shell2(t_process *p)
{
	if (ft_strequ(p->av[0], "jobs"))
		return (ft_jobs(p));
	else if (ft_strequ(p->av[0], "fc"))
		return (ft_fc(p));
	else if (ft_strequ(p->av[0], "export"))
		return (ft_export(p->ac, p->av));
	else if (ft_strequ(p->av[0], "set"))
		return (ft_set());
	else if (ft_strequ(p->av[0], "unset"))
		return (ft_unset(p->ac, p->av));
	else if (ft_strequ(p->av[0], "hash"))
		return (ft_hash(p));
	else if (ft_strequ(p->av[0], "type"))
		return (ft_type(p));
	else if (ft_strequ(p->av[0], "pwd"))
		return (ft_pwd(p));
	return (EXIT_FAILURE);
}

static int	lauch_process_which_can_change_shell(t_process *p)
{
	if (ft_strequ(p->av[0], "exit"))
		return (ft_exit(p));
	else if (ft_strequ(p->av[0], "alias"))
		return (ft_alias(p));
	else if (ft_strequ(p->av[0], "unalias"))
		return (ft_unalias(p));
	else if (ft_strequ(p->av[0], "cd"))
		return (ft_cd(p));
	else if (ft_strequ(p->av[0], "setenv"))
		return (ft_setenv(p));
	else if (ft_strequ(p->av[0], "unsetenv"))
		return (ft_unsetenv(p));
	else if (ft_strequ(p->av[0], "fg"))
		return (ft_fg(p));
	else if (ft_strequ(p->av[0], "bg"))
		return (ft_bg(p));
	else if (ft_strequ(p->av[0], "echo"))
		return (ft_echo(p));
	return (lauch_process_which_can_change_shell2(p));
}

int			lauch_in_parent_process(t_process *p)
{
	// int saved[3];
	// int old[3];
	// int ret;

	// prepare_saved_old_new_std(saved, old, p);
	// set_stdin_stdout_stderr_channels(old);
	if (handle_redirection(p) == EXIT_FAILURE)
	{
		// reset_stdin_stdout_stderr_channels(saved);
		return (EXIT_FAILURE);
	}
	// ret = lauch_process_which_can_change_shell(p);
	// reset_stdin_stdout_stderr_channels(saved);
	// return (ret);
	return (lauch_process_which_can_change_shell(p));
}
