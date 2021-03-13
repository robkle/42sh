/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_tools.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthan <dthan@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/12 21:09:04 by dthan             #+#    #+#             */
/*   Updated: 2021/03/13 19:20:26 by dthan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int	duplicating_file_descriptor(t_redi *redi, int old_fd)
{
	int			duplicated_fd;

	if (ft_atoi(redi->word) > 2)
	{
		ft_dprintf(2, "%s: %s: Bad file descriptor\n", "42sh", redi->word);
		return (EXIT_FAILURE);
	}
	if (redi->n)
		old_fd = ft_atoi(redi->n);
	duplicated_fd = dup(ft_atoi(redi->word));
	dup2(duplicated_fd, old_fd);
	close(duplicated_fd);
	return (EXIT_SUCCESS);
}

int	close_file_descriptor(t_redi *redi, int old_fd)
{
	if (redi->n && fcntl(ft_atoi(redi->n), F_GETFD) == -1)
	{
		ft_dprintf(2, "%s: %s: Bad file descriptor\n", "42s", redi->n);
		return (EXIT_FAILURE);
	}
	if (redi->n)
		old_fd = ft_atoi(redi->n);
	close(old_fd);
	return (EXIT_SUCCESS);
}
