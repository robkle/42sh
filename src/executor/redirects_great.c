/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirects_great.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthan <dthan@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/02 01:52:52 by tango             #+#    #+#             */
/*   Updated: 2020/10/01 04:20:51 by dthan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void			redirect_great(t_redirect *trav, t_process *p)
{
	int fd;

	if (!ft_strequ(trav->redirect_des, "-"))
	{
		fd = open(trav->redirect_des, O_WRONLY | O_TRUNC | O_CREAT, 0644);
		// need to return error when open fail
		p->stdout = fd;
	}
	else
		close(ft_atoi(trav->redirect_src));
}

void			redirect_dgreat(t_redirect *trav, t_process *p)
{
	int fd;

	if (!ft_strequ(trav->redirect_des, "-"))
	{
		fd = open(trav->redirect_des, O_WRONLY | O_APPEND | O_CREAT, 0644);
		// need to return error when open fail
		p->stdout = fd;
	}
	else
		close(ft_atoi(trav->redirect_src));
}

void			redirect_greatand(t_redirect *trav, t_process *p)
{
	int fd;

	if (!is_made_of_digits(trav->redirect_des) && \
		!ft_strequ("-", trav->redirect_des))
	{
		fd = open(trav->redirect_des, O_WRONLY | O_TRUNC | O_CREAT, 0644);
		// need to return error when open fail
		p->stdout = fd;
	}
	else if (is_made_of_digits(trav->redirect_des)) // check this later
		dup2(ft_atoi(trav->redirect_des), ft_atoi(trav->redirect_src));
	else
		close(ft_atoi(trav->redirect_src));
}
