/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthan <dthan@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/16 08:38:16 by dthan             #+#    #+#             */
/*   Updated: 2020/09/30 03:29:22 by dthan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int		execute_command(t_astnode *ast, t_list *heredoc, t_job *job)
{
	return (execute_simple_command(ast, heredoc, job));
}
