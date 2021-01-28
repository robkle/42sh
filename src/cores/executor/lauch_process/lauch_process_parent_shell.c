/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lauch_process_parent_shell.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthan <dthan@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/28 03:49:44 by dthan             #+#    #+#             */
/*   Updated: 2021/01/28 15:29:38 by dthan            ###   ########.fr       */
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
	return (EXIT_FAILURE);
}

static int	lauch_process_which_can_change_shell(t_process *p)
{
	if (ft_strequ(p->av[0], "exit"))
		return (ft_exit(EXIT_SUCCESS));
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

static void	prepare_saved_old_new_std(int saved[3], int old[3], t_process *p)
{
	saved[STDIN_FILENO] = STDIN_FILENO;
	saved[STDOUT_FILENO] = STDOUT_FILENO;
	saved[STDERR_FILENO] = STDERR_FILENO;
	(p->stdin != 0) ? saved[SAVED_STDIN] = dup(STDIN_FILENO) : 0;
	(p->stdout != 1) ? saved[SAVED_STDOUT] = dup(STDOUT_FILENO) : 0;
	(p->stderr != 2) ? saved[SAVED_STDERR] = dup(STDERR_FILENO) : 0;
	old[0] = p->stdin;
	old[1] = p->stdout;
	old[2] = p->stderr;
}

int			lauch_in_parent_process(t_process *p)
{
	int saved[3];
	int old[3];
	int ret;

	prepare_saved_old_new_std(saved, old, p);
	set_reset_stdin_stdout_stderr_channels(old);
	if (handle_redirection(p) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	ret = lauch_process_which_can_change_shell(p);
	set_reset_stdin_stdout_stderr_channels(saved);
	return (ret);
}
