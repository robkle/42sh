/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   access.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihwang <ihwang@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/15 23:35:55 by ihwang            #+#    #+#             */
/*   Updated: 2020/09/15 22:01:37 by ihwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int				possible_to_access_file(t_exe *c)
{
	if (c->av[0][0] == '.' || c->av[0][0] == '/')
	{
		if (access(c->av[0], F_OK))
		{
			error_monitor(c->av[0], ":No such file or dirrectory" \
			, NULL, EXIT_FAILURE);
			return (false);
		}
		else if (access(c->av[0], X_OK))
		{
			error_monitor(c->av[0], ": Permission denied" \
			, NULL, EXIT_FAILURE);
			return (false);
		}
		else
			return (true);
	}
	else
		return (false);
}
