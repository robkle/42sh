/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lauch_process_child_shell.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthan <dthan@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/28 03:49:29 by dthan             #+#    #+#             */
/*   Updated: 2021/03/10 22:00:53 by dthan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static int	is_builtin(char *cmd_name)
{
	if (ft_strequ(cmd_name, "exit") ||
		ft_strequ(cmd_name, "cd") ||
		ft_strequ(cmd_name, "pwd") ||
		ft_strequ(cmd_name, "env") ||
		ft_strequ(cmd_name, "setenv") ||
		ft_strequ(cmd_name, "unsetenv") ||
		ft_strequ(cmd_name, "jobs") ||
		ft_strequ(cmd_name, "fg") ||
		ft_strequ(cmd_name, "bg") ||
		ft_strequ(cmd_name, "echo") ||
		ft_strequ(cmd_name, "set") ||
		ft_strequ(cmd_name, "unset") ||
		ft_strequ(cmd_name, "hash") ||
		ft_strequ(cmd_name, "type"))
		return (1);
	return (0);
}

static int	exec_builtin2(t_process *p)
{
	if (ft_strequ(p->av[0], "echo"))
		return (ft_echo(p));
	else if (ft_strequ(p->av[0], "type"))
		return (ft_type(p));
	else if (ft_strequ(p->av[0], "set"))
		return (ft_set());
	else if (ft_strequ(p->av[0], "unset"))
		return (ft_unset(p->ac, p->av));
	else if (ft_strequ(p->av[0], "hash"))
		return (ft_hash(p));
	return (EXIT_FAILURE);
}

static int	exec_builtin(t_process *p)
{
	if (ft_strequ(p->av[0], "exit"))
		ft_exit(p);
	else if (ft_strequ(p->av[0], "cd"))
		return (ft_cd(p));
	else if (ft_strequ(p->av[0], "pwd"))
		return (ft_pwd(p));
	else if (ft_strequ(p->av[0], "env"))
		return (ft_env());
	else if (ft_strequ(p->av[0], "setenv"))
		return (ft_setenv(p));
	else if (ft_strequ(p->av[0], "unsetenv"))
		return (ft_unsetenv(p));
	else if (ft_strequ(p->av[0], "jobs"))
		return (ft_jobs_child(p));
	else if (ft_strequ(p->av[0], "fg"))
		return (ft_fg_child());
	else if (ft_strequ(p->av[0], "bg"))
		return (ft_bg_child());
	return (exec_builtin2(p));
}

static int	lauch_process(t_process *p, char *path)
{
	if (p->av[0] == NULL)
		return (EXIT_SUCCESS);
	if (ft_strchr(p->av[0], '/') != NULL && possible_to_access_file(p))
		return (make_child_binary(p));
	else if (is_builtin(p->av[0]))
		return (exec_builtin(p));
	else if (path != NULL)
		return (make_child_path_sub(p, path));
	//else if (is_in_path(p))
	//	return (make_child_path(p));
	//else if (possible_to_access_file(p))
	//	return (make_child_binary(p));
	else if (p->av[0][0] != '.' && p->av[0][0] != '/')
		ft_dprintf(2, "%s: %s: command not found\n", SHELL_NAME, p->av[0]);
	return (127);
}

static void	set_process_group_id(t_job *j, pid_t pid)
{
	if (j->pgid == 0)
		j->pgid = pid;
	setpgid(pid, j->pgid);
}

void handle_assignment_in_child_process(t_assignment *list)
{
	t_assignment *ptr;
	char *name;
	char *value;

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
	exit(lauch_process(p, path));
}

char	*is_in_hashtable(char *name)
{
	int		index;
	t_hash	*tmp;

	index = hash_index(name);
	tmp = g_shell.hashtable[index];
	while (tmp != NULL)
	{
		if (ft_strcmp(tmp->name, name) == 0)
		{
			tmp->hits++;
			return (tmp->path);
		}
		tmp = tmp->next;
	}
	return (NULL);
}

char	*get_path(t_process *p)
{
	char *path;

	if (p->av[0] == NULL) //add
		return (NULL);
	path = NULL;
	if (ft_strchr(p->av[0], '/'))
		return (NULL);
	if ((path = is_in_hashtable(p->av[0])))
		return (path);
	else
	{
		if ((path = find_executable(p->av[0])) != NULL)
		{
			add_hashentry(p->av[0], path, 1);
			free(path);
			path = is_in_hashtable(p->av[0]);
		}
		return (path);
	}
}

void	fork_and_launch_in_child_process(t_job *j, t_process *p)
{
	pid_t pid;
	char *path;

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
