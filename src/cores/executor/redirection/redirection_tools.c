/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_tools.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthan <dthan@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/12 21:09:04 by dthan             #+#    #+#             */
/*   Updated: 2021/03/12 21:09:19 by dthan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int	duplicating_file_descriptor(t_redi *redi, int old_fd)
{
	int			duplicated_fd;
	struct stat	statbuf;

	if (fstat(ft_atoi(redi->word), &statbuf) == -1 || ft_atoi(redi->word) > 2)
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
	int			dev_null;
	struct stat	statbuf;

	if (redi->n && fstat(ft_atoi(redi->n), &statbuf) == -1)
	{
		ft_dprintf(2, "%s: %s: Bad file descriptor\n", "42s", redi->n);
		return (EXIT_FAILURE);
	}
	dev_null = open("/dev/null", O_WRONLY);
	if (redi->n)
		dup2(dev_null, ft_atoi(redi->n));
	else
		dup2(dev_null, old_fd);
	close(dev_null);
	return (EXIT_SUCCESS);
}
