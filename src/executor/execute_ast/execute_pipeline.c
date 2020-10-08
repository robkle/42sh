/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_pipeline.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthan <dthan@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/16 08:36:24 by dthan             #+#    #+#             */
/*   Updated: 2020/10/08 12:59:54 by dthan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	initialize_job_position(t_job *j)
{
	if (j->foreground)
		put_job_in_foreground(j, 0);
	else
		put_job_in_background(j, 0);
}

void	execute_pipeline(t_astnode *ast, t_list **heredoc, t_job *job)
{
	execute_pipe_sequence(ast, heredoc, job);
	initialize_job_position(job);
}
