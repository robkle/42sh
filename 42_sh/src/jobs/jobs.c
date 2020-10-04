/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jobs.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthan <dthan@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/02 04:00:07 by dthan             #+#    #+#             */
/*   Updated: 2020/10/02 05:35:49 by dthan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/shell.h"

int ft_jobs(void)
{
	t_list *j_ptr;
	t_job *j;
	int i;

	i = 1;
	j_ptr = g_shell.job;
	while (j_ptr)
	{
			ft_printf("HERE\n");
		j = (t_job*)j_ptr->content;
		//output will be deferent when a process is finished
		ft_printf("[%d]  +  %d  running  %s\n", i++, j->pgid, j->command);
		j_ptr = j_ptr->next; 
	}
	return (EXIT_SUCCESS);
}
