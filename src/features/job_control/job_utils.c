/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   job_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthan <dthan@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/26 03:29:07 by dthan             #+#    #+#             */
/*   Updated: 2020/12/18 18:19:41 by dthan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static int get_job_id()
{
	int id;
	t_job *j_ptr;

	id = 1;
	j_ptr = g_shell.first_job;
	while(j_ptr)
	{
		if (id != j_ptr->id)
			break;
		id++;
		j_ptr = j_ptr->next;
	}
	return (id);
}


void put_to_list_job(t_job *newjob)
{
	t_job *j_ptr;

	if (newjob == NULL)
		return ;
	if (g_shell.first_job == NULL)
		g_shell.first_job = newjob;
	else
	{
		j_ptr = g_shell.first_job;
		while (j_ptr->next != NULL)
			j_ptr = j_ptr->next;
		j_ptr->next = newjob;
	}
}

t_job	*create_job(int foreground, int forked)
{
	t_job *j;

	j = ft_memalloc(sizeof(t_job));
	j->command = NULL;
	j->pgid = 0;
	j->notified = 0;
	tcgetattr(STDIN_FILENO, &j->term);
	j->first_process = NULL;
	j->stdin = STDIN_FILENO;
	j->stdout = STDOUT_FILENO;
	j->stderr = STDERR_FILENO;
	j->foreground = foreground;
	j->forked = forked;
	j->id = get_job_id();
	j->pipe_fd_closer[0] = 0;
	j->pipe_fd_closer[1] = 0;
	j->next = NULL;
	return (j);
}

static void delete_redi(t_process* p)
{
	t_redi *p_redi;
	t_redi *temp_redi;

	if (p->first_redi == NULL)
		return ;
	p_redi = p->first_redi;
	while (p_redi)
	{
		temp_redi = p_redi;
		p_redi = p_redi->next;
		if (temp_redi->n)
			free(temp_redi->n);
		if (temp_redi->op)
			free(temp_redi->op);
		if (temp_redi->word)
			free(temp_redi->word);
		free(temp_redi);
	}
}

static void delete_process(t_job *j)
{
	t_process *p_ptr;
	t_process *temp_process;
	int i;

	if (j->first_process == NULL)
		return ;
	p_ptr = j->first_process;
	while(p_ptr)
	{
		temp_process = p_ptr;
		p_ptr = p_ptr->next;
		delete_redi(temp_process);
		i = -1;
		while (temp_process->av[++i] && i < MAX_ARGV)
			free(temp_process->av[i]);
		free(temp_process->av);
		free(temp_process);
	}
}

void delete_job(t_job *j, char option)
{
	if (option && job_is_stopped(j) && !job_is_completed(j))
	{
		if (kill(- j->pgid, SIGCONT) < 0)
			perror("kill (SIGCONT)"); // need to replace error string
		kill(- j->pgid, SIGTERM);
	}
	delete_process(j);
	free(j->command);
	free(j);
}

void delete_jobs(t_job *j_ptr, char option)
{
	t_job *temp_job;

	while (j_ptr)
	{
		temp_job = j_ptr;
		j_ptr = j_ptr->next;
		delete_job(temp_job, option);
	}
}

t_job *find_job(pid_t pgid)
{
	t_job *j_ptr;

	j_ptr = g_shell.first_job;
	while (j_ptr)
	{
		if (j_ptr->pgid == pgid)
			return (j_ptr);
		j_ptr = j_ptr->next;
	}
	return (NULL);
}

void job_command_builder(int argc, t_job *j, ...)
{
	va_list ap;
	int i;

	i = 0;
	va_start(ap, j);
	while (i++ < argc)
		j->command = ft_strjoin_and_free_string1(j->command, va_arg(ap, char*));
	va_end(ap);
}

void print_job_background(t_job *j)
{
	int i;
	t_job *j_ptr;

	i = 0;
	j_ptr = g_shell.first_job;
	while(j_ptr)
	{
		i++;
		if (j_ptr == j)
			break ;
		j_ptr = j_ptr->next;
	}
	ft_printf("[%d] %d\n", i, j->pgid);
}

t_job *is_valid_job_id(char *str)
{
	int job_id;
	t_job *j_ptr;

	if (!is_number_str(str))
	{
		if (str[0] && str[0] == '%' && is_number_str(&str[1]))
			job_id = ft_atoi(&str[1]);
		else
			return (NULL);
	}
	else
		job_id = ft_atoi(str);
	j_ptr = g_shell.first_job;
	while (j_ptr)
	{
		if (job_id == j_ptr->id)
			return (j_ptr);
		j_ptr = j_ptr->next;
	}
	return (NULL);	
}

int is_number_str(char *str)
{
	int i;

	i = -1;
	if (str == NULL)
		return (0);
	while (str[++i])
		if (!ft_isdigit(str[i]))
			return (0);
	return (1);
}

t_job *find_the_current_job()
{
	t_job *j_ptr;
	t_job *current_job;
	int add;

	j_ptr = g_shell.first_job;
	current_job = NULL;
	add = 0;
	while (j_ptr)
	{
		if (job_is_stopped(j_ptr))
		{
			current_job = j_ptr;
			add = 1;
		}
		else if (!add)
			current_job = j_ptr;
		j_ptr = j_ptr->next;	
	}
	return (current_job);
}

int is_the_current_job(t_job *j)
{
	t_job *current_job;

	current_job = find_the_current_job();
	if (j == NULL || current_job == NULL)
		return (0);
	return (current_job == j);
}

int count_nb_suspended_job()
{
	int ct;
	t_job *j_ptr;

	j_ptr = g_shell.first_job;
	ct = 0;
	while (j_ptr)
	{
		if (job_is_stopped(j_ptr))
			ct++;
		j_ptr = j_ptr->next;
	}
	return (ct);
}

t_job *find_the_last_job()
{
	t_job *last_job;
	t_job *j_ptr;
	t_job *current_job;

	last_job = NULL;
	int add;

	add = (count_nb_suspended_job() > 1) ? 1 : 0;
	current_job = find_the_current_job();
	j_ptr = g_shell.first_job;
	if (!j_ptr || !current_job)
		return NULL;
	while (j_ptr)
	{
		if (add)
		{
			if (j_ptr != current_job && job_is_stopped(j_ptr))
				last_job = j_ptr;
		}
		else
		{
			if (j_ptr != current_job)
				last_job = j_ptr;
		}
		j_ptr = j_ptr->next;
	}
	return (last_job);
}

int is_the_last_job(t_job *j)
{
	t_job *last_job;

	if (j == NULL)
		return (0);
	last_job = find_the_last_job();
	if (last_job == NULL)
		return (0);
	return (last_job == j);
}
