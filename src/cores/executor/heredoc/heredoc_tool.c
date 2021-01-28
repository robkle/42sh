/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_tool.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthan <dthan@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/28 02:59:04 by dthan             #+#    #+#             */
/*   Updated: 2021/01/28 13:21:52 by dthan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	clear_heredoc(t_heredoc *heredoc)
{
	t_heredoc *container;

	while (heredoc)
	{
		container = heredoc;
		heredoc = heredoc->next;
		free(container->doc);
		free(container);
	}
}
