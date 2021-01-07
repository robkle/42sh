/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig_handler.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthan <dthan@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/18 04:00:37 by dthan             #+#    #+#             */
/*   Updated: 2021/01/06 01:13:05 by dthan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static void	sig_int_handler(int sig)
{
	(void)sig;
	g_shell.signal_indicator = SIGINT;
	ioctl(1, TIOCSTI, "");
}

static void	sig_winch_handler(int sig)
{
	(void)sig;
	g_shell.signal_indicator = SIGWINCH;
	if (!(tgetent(NULL, getenv("TERM"))))
	{
		ft_putstr_fd("Environment variable 'TERM' not set \n", 2);
		ft_exit(EXIT_FAILURE);
	}
	ioctl(1, TIOCSTI, "");
}

void		sig_controller(int option)
{
	if (option == PARENT)
	{
		signal(SIGSTOP, SIG_IGN);
    	signal(SIGTSTP, SIG_IGN);
    	signal(SIGTTIN, SIG_IGN);
    	signal(SIGTTOU, SIG_IGN);
    	signal(SIGCHLD, SIG_DFL);
		signal(SIGPIPE, SIG_IGN);
    	// signal (SIGCHLD, SIG_IGN);
		signal(SIGINT, sig_int_handler);
		signal(SIGWINCH, sig_winch_handler);
	}
	else if (option == CHILD)
	{
		int i;
		i = 1;
		while (i < 32)
		{
			signal(i, SIG_DFL);
			i++;
		}
	}
}
