/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig_handler.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihwang <ihwang@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/18 04:00:37 by dthan             #+#    #+#             */
/*   Updated: 2021/02/04 19:11:20 by ihwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static void	sig_int_handler(int sig)
{
	(void)sig;
	g_shell.signal_indicator = SIGINT;
	g_shell.exit_status = 1;
	ioctl(1, TIOCSTI, "");
}

static void	sig_winch_handler(int sig)
{
	(void)sig;
	g_shell.signal_indicator = SIGWINCH;
	if (!(tgetent(NULL, getenv("TERM"))))
	{
		ft_putstr_fd("Environment variable 'TERM' not set \n", 2);
		ft_exit_internal(EXIT_FAILURE);
	}
	ioctl(1, TIOCSTI, "");
}

void		sig_controller(int option)
{
	if (option == PARENT)
	{
		/*
		** when shell is interactive, this shell will ignore
		** SIGTERM, SIGQUIT
		*/
		signal(SIGTERM, SIG_IGN);
		signal(SIGQUIT, SIG_IGN);
		
		/*
		** When job control is in effect, this shell will ignore
		** SIGTTIN, SIGTTOU, SIGTSTP
		*/
		signal(SIGTTIN, SIG_IGN);
		signal(SIGTTOU, SIG_IGN);
		signal(SIGTSTP, SIG_IGN);
		/*
		** This shell will exit by default upon receipt of SIGHUP
		*/
		/*
		** SIGCHILD is put to default to cauch the status of child process
		*/
    	signal(SIGCHLD, SIG_DFL);
		/*
		** Sigpipe is put to ignore to handle broken pipe in redirection
		*/
		signal(SIGPIPE, SIG_IGN);
		signal(SIGINT, sig_int_handler);
		signal(SIGWINCH, sig_winch_handler);
		/*
		** unknow signal
		*/
		signal(SIGSTOP, SIG_IGN);
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
