/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete_process_tools.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthan <dthan@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/28 17:27:01 by dthan             #+#    #+#             */
/*   Updated: 2021/01/28 17:27:37 by dthan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	delete_redi(t_process *p)
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

void	delete_process(t_job *j)
{
	t_process	*p_ptr;
	t_process	*temp_process;
	int			i;

	if (j->first_process == NULL)
		return ;
	p_ptr = j->first_process;
	while (p_ptr)
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