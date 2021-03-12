/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirects_less.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthan <dthan@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/02 01:52:52 by tango             #+#    #+#             */
/*   Updated: 2021/03/12 21:13:56 by dthan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int	redirect_lessand(t_redi *redi)
{
	if (ft_strequ(redi->word, "-"))
		return (close_file_descriptor(redi, STDIN_FILENO));
	if (!is_made_of_digits(redi->word))
	{
		ft_dprintf(2, "%s: %s: ambiguous redirect\n", "42sh", redi->word);
		return (EXIT_FAILURE);
	}
	return (duplicating_file_descriptor(redi, STDIN_FILENO));
}

int	redirect_less(t_redi *redi)
{
	int new_fd;
	int old_fd;

	new_fd = STDIN_FILENO;
	if (redi->n)
		new_fd = ft_atoi(redi->n);
	old_fd = open(redi->word, O_RDONLY);
	if (old_fd == -1)
	{
		ft_dprintf(STDERR_FILENO, "%s: no such file or directory: %s\n", \
			SHELL_NAME, redi->word);
		return (EXIT_FAILURE);
	}
	dup2(old_fd, new_fd);
	close(old_fd);
	return (EXIT_SUCCESS);
}

int	redirect_dless(t_redi *redi)
{
	int fd[2];

	pipe(fd);
	if (redi->word)
		ft_putstr_fd(redi->word, fd[WRITE_END]);
	close(fd[WRITE_END]);
	dup2(fd[READ_END], STDIN_FILENO);
	close(fd[READ_END]);
	return (EXIT_SUCCESS);
}
