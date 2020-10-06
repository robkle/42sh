/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   job_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthan <dthan@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/26 03:29:07 by dthan             #+#    #+#             */
/*   Updated: 2020/10/06 17:23:16 by dthan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

t_list	*create_job(void)
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
	j.foreground = 1;
	node = ft_lstnew(&j, sizeof(t_job));
	return (node);
}

void put_to_list_job(t_list *newjob)
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

t_list *findjob(pid_t pgid)
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
