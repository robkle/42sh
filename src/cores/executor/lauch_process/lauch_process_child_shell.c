/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lauch_process_child_shell.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthan <dthan@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/28 03:49:29 by dthan             #+#    #+#             */
/*   Updated: 2021/03/12 20:50:47 by dthan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static void	set_process_group_id(t_job *j, pid_t pid)
{
	if (j->pgid == 0)
		j->pgid = pid;
	setpgid(pid, j->pgid);
}

static void	handle_assignment_in_child_process(t_assignment *list)
{
	t_assignment	*ptr;
	char			*name;
	char			*value;

	ptr = list;
	while (ptr)
	{
		name = ft_strndup(ptr->data, ft_strchr(ptr->data, '=') - &ptr->data[0]);
		value = ft_strdup(ft_strchr(ptr->data, '=') + 1);
		add_update_environment_var(name, value);
		(name) ? free(name) : 0;
		(value) ? free(value) : 0;
		ptr = ptr->next;
	}
}

static void	lauch_in_child_process(t_job *j, t_process *p, char *path)
{
	(j->pipe_fd_closer[0]) ? close(j->pipe_fd_closer[0]) : 0;
	(j->pipe_fd_closer[1]) ? close(j->pipe_fd_closer[1]) : 0;
	if (p->first_assignment)
		handle_assignment_in_child_process(p->first_assignment);
	if (handle_redirection(p) == EXIT_FAILURE)
		exit(EXIT_FAILURE);
	set_process_group_id(j, getpid());
	if (j->foreground)
		ft_tcsetpgrp(STDIN_FILENO, j->pgid);
	sig_controller(CHILD);
	exit(execute_in_child_process(p, path));
}

void		fork_and_launch_in_child_process(t_job *j, t_process *p)
{
	pid_t	pid;
	char	*path;

	path = get_path(p);
	pid = fork();
	if (pid == 0)
		lauch_in_child_process(j, p, path);
	else if (pid < 0)
	{
		ft_putstr_fd("Fork failed at lauching child process\n", 2);
		exit(EXIT_FAILURE);
	}
	p->pid = pid;
	set_process_group_id(j, pid);
}
