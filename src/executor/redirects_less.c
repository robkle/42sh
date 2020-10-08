/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirects_less.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthan <dthan@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/02 01:52:52 by tango             #+#    #+#             */
/*   Updated: 2020/10/01 04:18:29 by dthan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void		redirect_lessand(t_redirect *trav, t_process *p)
{
	t_stat	sb;
	int		fd;

	fd = ft_atoi(trav->redirect_src);
	if (!is_made_of_digits(trav->redirect_src) && \
			!ft_strequ(trav->redirect_src, "-"))
	{
		error_monitor(SYNTAX_AMBIG_REDI, trav->redirect_src, NULL, 1);
		ft_exit(EXIT_FAILURE);
	}
	else if (ft_strequ(trav->redirect_src, "-"))
		close(ft_atoi(trav->redirect_des));
	else if ((fstat(fd, &sb)) < 0)
	{
		error_monitor(SYNTAX_BAD_FD, trav->redirect_src, NULL, 1);
		ft_exit(EXIT_FAILURE);
	}
	else if (!(sb.st_mode & S_IRUSR))
	{
		error_monitor(SYNTAX_BAD_FD, trav->redirect_src, NULL, 1);
		ft_exit(EXIT_FAILURE);
	}
	else
		p->stdin = fd;
}

void		redirect_less(t_redirect *trav, t_process *p)
{
	int fd;

	fd = open(trav->redirect_src, O_RDONLY);
	if (fd == -1)
		error_monitor(SHELL_ENOENT, trav->redirect_src, NULL, 0);
	p->stdin = fd;
}

void		redirect_dless(t_redirect *trav, t_process *p)
{
	int fd[2];

	pipe(fd);
	ft_putstr_fd(trav->redirect_src, fd[WRITE_END]);
	close(fd[WRITE_END]);
	p->stdin = fd[READ_END];
}
