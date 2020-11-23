/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirects_less.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthan <dthan@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/02 01:52:52 by tango             #+#    #+#             */
/*   Updated: 2020/10/30 05:54:15 by dthan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

// respectively the same as close file descriptor for great-and
int close_file_descriptor2(t_redi *redi, t_process *p)
{
	int dev_null;
	struct stat statbuf;

	if (redi->n && fstat(ft_atoi(redi->n), &statbuf) == -1)
	{
		ft_dprintf(2, "%s: %s: Bad file descriptor\n", "42s", redi->n);
		return (EXIT_FAILURE);
	}
	dev_null = open("/dev/null", O_WRONLY);
	if (redi->n)
		dup2(dev_null, ft_atoi(redi->n));
	else
		dup2(dev_null, p->stdin);
	close(dev_null);
	return (EXIT_SUCCESS);
}

int duplicating_file_descriptor2(t_redi *redi, t_process *p)
{
	int duplicated_fd;
	int old_fd;
	struct stat statbuf;

	if (fstat(ft_atoi(redi->word), &statbuf) == -1)
	{
		ft_dprintf(2, "%s: %s: Bad file descriptor\n", "42sh", redi->word);
		return (EXIT_FAILURE);
	}
	old_fd = p->stdin;
	if (redi->n)
		old_fd = ft_atoi(redi->n);
	duplicated_fd = dup(ft_atoi(redi->word));
	dup2(duplicated_fd, old_fd);
	close(duplicated_fd);
	return (EXIT_SUCCESS);
}

int		redirect_lessand(t_redi *redi, t_process *p)
{
	if (ft_strequ(redi->word, "-"))
		return (close_file_descriptor2(redi, p));
	if (!is_made_of_digits(redi->word))
	{
		ft_dprintf(2, "%s: %s: ambiguous redirect\n", "42sh", redi->word);
		return (EXIT_FAILURE);
	}
	return (duplicating_file_descriptor2(redi, p));
}

int		redirect_less(t_redi *redi, t_process *p)
{
	int new_fd;
	int old_fd;

	new_fd = p->stdin;
	if (redi->n)
		new_fd = ft_atoi(redi->n);
	old_fd = open(redi->word, O_RDONLY);
	if (old_fd == -1)
	{
		ft_dprintf(STDERR_FILENO, "%s: %s: %s\n", \
				SHELL_NAME, ENOENT, redi->word);
		return (EXIT_FAILURE);
	}
	dup2(old_fd, new_fd);
	close(old_fd);
	return (EXIT_SUCCESS);
}

int		redirect_dless(t_redi *redi, t_process *p)
{
	int fd[2];

	pipe(fd);
	ft_putstr_fd(redi->word, fd[WRITE_END]);
	close(fd[WRITE_END]);
	dup2(fd[READ_END], p->stdin);
	close(fd[READ_END]);
	return (EXIT_SUCCESS);
}
