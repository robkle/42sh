/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthan <dthan@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/16 08:38:16 by dthan             #+#    #+#             */
/*   Updated: 2020/10/06 16:36:01 by dthan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	execute_command(t_astnode *ast, t_list **heredoc, t_job *j, t_process *p)
{
	return (execute_simple_command(ast, heredoc, j, p));
}
