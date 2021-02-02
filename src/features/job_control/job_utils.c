/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   job_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthan <dthan@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/26 03:29:07 by dthan             #+#    #+#             */
/*   Updated: 2021/01/28 17:39:49 by dthan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void		put_to_list_job(t_job *newjob)
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

t_job		*find_job(pid_t pgid)
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

void		job_command_builder(int argc, t_job *j, ...)
{
	va_list	ap;
	int		i;

	i = 0;
	va_start(ap, j);
	while (i++ < argc)
		j->command = ft_strjoin_and_free_string1(j->command, va_arg(ap, char*));
	va_end(ap);
}

t_job		*is_valid_job_id(char *str)
{
	int		job_id;
	t_job	*j_ptr;

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

t_job	*find_the_current_job(void)
{
	t_job	*j_ptr;
	t_job	*current_job;
	int		add;

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



int		count_nb_suspended_job(void)
{
	int		ct;
	t_job	*j_ptr;

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

t_job	*find_the_last_job(void)
{
	t_job	*last_job;
	t_job	*j_ptr;
	t_job	*current_job;
	int		add;

	last_job = NULL;
	add = (count_nb_suspended_job() > 1) ? 1 : 0;
	current_job = find_the_current_job();
	j_ptr = g_shell.first_job;
	if (!j_ptr || !current_job)
		return (NULL);
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

int		is_the_last_job(t_job *j)
{
	t_job *last_job;

	if (j == NULL)
		return (0);
	last_job = find_the_last_job();
	if (last_job == NULL)
		return (0);
	return (last_job == j);
}
