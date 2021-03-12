/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirects_great.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthan <dthan@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/02 01:52:52 by tango             #+#    #+#             */
/*   Updated: 2021/03/12 21:14:02 by dthan            ###   ########.fr       */
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

int	redirect_greatand(t_redi *redi)
{
	if (ft_strequ(redi->word, "-"))
		return (close_file_descriptor(redi, STDOUT_FILENO));
	else if (!is_made_of_digits(redi->word))
		return (redirecting_stdout_and_stderr(redi));
	return (duplicating_file_descriptor(redi, STDOUT_FILENO));
}
