/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_pipeline.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthan <dthan@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/16 08:36:24 by dthan             #+#    #+#             */
/*   Updated: 2020/09/30 03:29:11 by dthan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int		execute_pipeline(t_astnode *ast, t_list *heredoc, t_job *job)
{
	return (execute_pipe_sequence(ast, heredoc, job));
}
