/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthan <dthan@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/13 12:05:30 by dthan             #+#    #+#             */
/*   Updated: 2020/10/13 12:32:32 by dthan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static void put_to_plist(t_list *new_process, t_list **first_process)
{
	if (*first_process == NULL)
		*first_process = new_process;
	else
		ft_lstadd_tail(first_process, new_process);
}

t_process	*create_process(t_job *j)
{
	t_process process;
	t_list		*node;

	process.av = (char**)ft_memalloc(sysconf(_SC_ARG_MAX));
	process.ac = 0;
	process.pid = 0;
	process.stdin = j->stdin;
	process.stdout = j->stdout;
	process.stderr = j->stderr;
	process.redi = NULL;
	process.completed = NOT_COMPLETED;
	process.stopped = NOT_STOPPED;
	process.status = UNAVAILABLE_STATUS;
	node = ft_lstnew(&process, sizeof(t_process));
	put_to_plist(node, &j->first_process);
	return ((t_process*)(node->content));
}

int last_process_status(t_job *job)
{
	t_list *p_ptr;
	t_process *p;

	p_ptr = job->first_process;
	while (p_ptr && p_ptr->next)
		p_ptr = p_ptr->next;
	p = (t_process*)p_ptr->content;
	return (p->status);
}
