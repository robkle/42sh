/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lauch_process.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthan <dthan@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/05 03:14:55 by dthan             #+#    #+#             */
/*   Updated: 2021/02/15 23:43:33 by dthan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int		is_execute_on_parent_process(int foreground, char *cmd_name)
{
	if (!foreground)
		return (0);
	if (ft_strequ(cmd_name, "exit") ||
		ft_strequ(cmd_name, "alias") ||
		ft_strequ(cmd_name, "unalias") ||
		ft_strequ(cmd_name, "cd") ||
		ft_strequ(cmd_name, "setenv") ||
		ft_strequ(cmd_name, "unsetenv") ||
		ft_strequ(cmd_name, "jobs") ||
		ft_strequ(cmd_name, "fg") ||
		ft_strequ(cmd_name, "bg") ||
		ft_strequ(cmd_name, "fc") ||
		ft_strequ(cmd_name, "export") ||
		ft_strequ(cmd_name, "set") ||
		ft_strequ(cmd_name, "unset") ||
		ft_strequ(cmd_name, "echo") ||
		ft_strequ(cmd_name, "hash") ||
		ft_strequ(cmd_name, "pwd") ||
		ft_strequ(cmd_name, "type"))
		return (1);
	return (0);
}

void	prepare_saved_old_new_std(int saved[3], int old[3], t_process *p)
{
	saved[SAVED_STDIN] = dup(STDIN_FILENO);
	saved[SAVED_STDOUT] = dup(STDOUT_FILENO);
	saved[SAVED_STDERR] = dup(STDERR_FILENO);
	old[0] = p->stdin;
	old[1] = p->stdout;
	old[2] = p->stderr;
}

int		lauch_simple_command(t_job *j, t_process *p)
{
	int saved[3];
	int old[3];

	if (handle_expansion(p) == EXIT_FAILURE)
	{
		p->status = EXIT_FAILURE;
		p->completed = COMPLETED;
		return (EXIT_FAILURE);
	}
	prepare_saved_old_new_std(saved, old, p);
	set_stdin_stdout_stderr_channels(old);
	if (is_execute_on_parent_process(j->foreground, p->av[0]))
	{
		p->status = lauch_in_parent_process(p);
		p->completed = COMPLETED;
	}
	else
		fork_and_launch_in_child_process(j, p);
	reset_stdin_stdout_stderr_channels(saved);
	return ((p->status == NOT_COMPLETED) ? g_shell.exit_status : p->status);
}
