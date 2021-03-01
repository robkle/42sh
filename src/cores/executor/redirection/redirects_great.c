/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirects_great.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthan <dthan@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/02 01:52:52 by tango             #+#    #+#             */
/*   Updated: 2021/02/25 06:13:50 by dthan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int	redirect_great(t_redi *redi)
{
	int new_fd;
	int old_fd;

	new_fd = STDOUT_FILENO;
	if (redi->n)
		new_fd = ft_atoi(redi->n);
	old_fd = open(redi->word, O_WRONLY | O_TRUNC | O_CREAT, 0644);
	if (old_fd == -1)
	{
		ft_dprintf(STDERR_FILENO, "%s: no such file or directory: %s\n",
			SHELL_NAME, redi->word);
		return (EXIT_FAILURE);
	}
	dup2(old_fd, new_fd);
	close(old_fd);
	return (EXIT_SUCCESS);
}

int	redirect_dgreat(t_redi *redi)
{
	int new_fd;
	int old_fd;

	new_fd = STDOUT_FILENO;
	if (redi->n)
		new_fd = (ft_atoi(redi->n));
	old_fd = open(redi->word, O_WRONLY | O_APPEND | O_CREAT, 0644);
	if (old_fd == -1)
	{
		ft_dprintf(STDERR_FILENO, "%s: no such file or directory: %s\n",
			SHELL_NAME, redi->word);
		return (EXIT_FAILURE);
	}
	dup2(old_fd, new_fd);
	close(old_fd);
	return (EXIT_SUCCESS);
}

int	redirecting_stdout_and_stderr(t_redi *redi)
{
	int old_fd;

	if (redi->n && ft_atoi(redi->n) != 1)
	{
		ft_dprintf(2, "%s: %s: ambiguous redirect\n", "42sh", redi->word);
		return (EXIT_FAILURE);
	}
	old_fd = open(redi->word, O_WRONLY | O_TRUNC | O_CREAT, 0644);
	if (old_fd == -1)
	{
		ft_dprintf(STDERR_FILENO, "%s: no such file or directory: %s\n",
			SHELL_NAME, redi->word);
		return (EXIT_FAILURE);
	}
	dup2(old_fd, STDOUT_FILENO);
	dup2(old_fd, STDERR_FILENO);
	close(old_fd);
	return (EXIT_SUCCESS);
}

int	duplicating_file_descriptor(t_redi *redi)
{
	int			duplicated_fd;
	int			old_fd;
	struct stat	statbuf;

	if (fstat(ft_atoi(redi->word), &statbuf) == -1 || ft_atoi(redi->word) > 2)
	{
		ft_dprintf(2, "%s: %s: Bad file descriptor\n", "42sh", redi->word);
		return (EXIT_FAILURE);
	}
	old_fd = STDOUT_FILENO;
	if (redi->n)
		old_fd = ft_atoi(redi->n);
	duplicated_fd = dup(ft_atoi(redi->word));
	dup2(duplicated_fd, old_fd);
	close(duplicated_fd);
	return (EXIT_SUCCESS);
}

int	close_file_descriptor(t_redi *redi)
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
		dup2(dev_null, STDOUT_FILENO);
	close(dev_null);
	return (EXIT_SUCCESS);
}

int	redirect_greatand(t_redi *redi)
{
	if (ft_strequ(redi->word, "-"))
		return (close_file_descriptor(redi));
	else if (!is_made_of_digits(redi->word))
		return (redirecting_stdout_and_stderr(redi));
	return (duplicating_file_descriptor(redi));
}
