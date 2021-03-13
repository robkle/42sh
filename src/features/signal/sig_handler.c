/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig_handler.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthan <dthan@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/18 04:00:37 by dthan             #+#    #+#             */
/*   Updated: 2021/03/14 01:23:17 by dthan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void		sig_int_handler(int sig)
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

/*
** when shell is interactive, this shell will ignore
** SIGTERM, SIGQUIT
** When job control is in effect, this shell will ignore
** SIGTTIN, SIGTTOU, SIGTSTP
** This shell will exit by default upon receipt of SIGHUP
** SIGCHILD is put to default to cauch the status of child process
** Sigpipe is put to ignore to handle broken pipe in redirection
** unknow use of signal SIGSTOP
*/

static void	sig_control_parent_shell(void)
{
	signal(SIGTERM, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGTTIN, SIG_IGN);
	signal(SIGTTOU, SIG_IGN);
	signal(SIGTSTP, SIG_IGN);
	signal(SIGCHLD, SIG_DFL);
	signal(SIGPIPE, SIG_IGN);
	signal(SIGINT, sig_int_handler);
	signal(SIGWINCH, sig_winch_handler);
	signal(SIGSTOP, SIG_IGN);
}

static void	sig_control_child_shell(void)
{
	int i;

	i = 1;
	while (i < 32)
		signal(i++, SIG_DFL);
}

void		sig_controller(int option)
{
	if (option == PARENT)
		sig_control_parent_shell();
	else if (option == CHILD)
		sig_control_child_shell();
}
