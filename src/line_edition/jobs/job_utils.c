/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   job_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthan <dthan@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/26 03:29:07 by dthan             #+#    #+#             */
/*   Updated: 2020/10/16 15:15:22 by dthan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static void put_to_list_job(t_list *newjob)
{
	t_list *j_ptr;

	if (newjob == NULL)
		return ;
	j_ptr = g_shell.first_job;
	while (j_ptr && j_ptr->next != NULL)
		j_ptr = j_ptr->next;
	if (j_ptr == NULL)
		g_shell.first_job = newjob;
	else
		j_ptr->next = newjob;
}

static int get_job_id()
{
	int id;
	t_list *j_ptr;
	t_job *j;

	id = 1;
	j_ptr = g_shell.first_job;
	while(j_ptr)
	{
		j = (t_job*)(j_ptr->content);
		if (id != j->id)
			break;
		id++;
		j_ptr = j_ptr->next;
	}
	return (id);
}

t_job	*create_job(int foreground, int forked)
{
	t_job j;
	t_list *node;

	j.command = NULL;
	j.pgid = 0;
	j.notified = 0;
	tcgetattr(STDIN_FILENO, &j.term);
	j.first_process = NULL;
	j.stdin = STDIN_FILENO;
	j.stdout = STDOUT_FILENO;
	j.stderr = STDERR_FILENO;
	j.foreground = foreground;
	j.forked = forked;
	j.id = get_job_id();
	node = ft_lstnew(&j, sizeof(t_job));
	put_to_list_job(node);
	return ((t_job*)(node->content));
}

void delete_job(t_list *j)
{
	t_list *p_ptr;
	t_list	*p_temp;
	

	if (j == NULL)
		return ;
	p_ptr = ((t_job*)(j->content))->first_process;
	while(p_ptr)
	{
		p_temp = p_ptr;
		p_ptr = p_ptr->next;
		free(p_temp);
	}
	free(j);
}

t_list *find_job(pid_t pgid)
{
	t_list *j_ptr;

	j_ptr = g_shell.first_job;
	while (j_ptr)
	{
		if (((t_job*)(j_ptr->content))->pgid == pgid)
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

void print_job_background(t_list *job_node)
{
	int i;
	t_list *j_ptr;

	i = 0;
	j_ptr = g_shell.first_job;
	while(j_ptr)
	{
		i++;
		if (j_ptr == job_node)
			break ;
		j_ptr = j_ptr->next;
	}
	ft_printf("[%d] %d\n", i, ((t_job*)(job_node->content))->pgid);
}

int is_valid_job_id(t_job *current_job, char *str)
{
	int job_id;
	t_list *j_ptr;
	t_job *j;

	if (!is_number_str(str) || \
		(str[1] && str[1] == '%' && !is_number_str(&str[1])))
		return (0);
	job_id = ft_atoi(str);
	j_ptr = g_shell.first_job;
	while (j_ptr)
	{
		j = (t_job*)(j_ptr->content);
		if (j != current_job && job_id == j->id)
			return (job_id);
		j_ptr = j_ptr->next;
	}
	return (0);	
}

t_job *find_job_with_id(int job_id)
{
	t_list *j_ptr;
	t_job *j;

	j_ptr = g_shell.first_job;
	while(j_ptr)
	{
		j = (t_job*)(j_ptr->content);
		if (job_id == j->id)
			return (j);
		j_ptr = j_ptr->next;
	}
	return (NULL);
}

t_job *find_the_last_job(t_job *current_j)
{
	t_list *j_ptr;
	t_job *ret;

	if (!g_shell.first_job)
		return (NULL);
	ret = NULL;
	j_ptr = g_shell.first_job;
	while (j_ptr)
	{
		if ((t_job*)(j_ptr->content) != current_j)
			ret = (t_job*)(j_ptr->content);
		j_ptr = j_ptr->next;
	}
	return (ret);
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
