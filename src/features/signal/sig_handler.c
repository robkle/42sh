/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig_handler.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthan <dthan@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/18 04:00:37 by dthan             #+#    #+#             */
/*   Updated: 2020/12/27 17:44:25 by dthan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void post_sigint(t_l *l)
{
	int tmp_pmpt;
	int current_row;

	tmp_pmpt = l->pmpt;
	current_row = get_current_row();
	apply_termcap_str("cm", l->x, current_row - 1);
	apply_termcap_str("cd", 0, 0);
	ft_strdel(&l->line);
	ft_memset(l, 0, sizeof(*l));
	l->total_row = tgetnum("li");
	l->starting_row = l->total_row - current_row;
	l->pmpt = tmp_pmpt;
	l->x = l->pmpt;
	l->co = tgetnum("co");
	ft_putchar('\n');
	get_prompt();
	g_shell.signal_indicator = 0;
	g_shell.history->hst = g_shell.history->curr;//NEW
	up_down(l, NULL); //NEW
}

static void sig_int_handler(int sig)
{
	(void)sig;
	g_shell.signal_indicator = SIGINT;
	ioctl(1, TIOCSTI, "");
}

void			post_sigwinch(t_l *l)
{
	int			len_pmpt;

	apply_termcap_str("cl", 0, 0);
	len_pmpt = get_prompt() - l->pmpt;
	l->co = tgetnum("co");
	l->total_row = tgetnum("li");
	l->starting_row = l->total_row - get_current_row();
	l->x = l->pmpt;
	l->y = 0;
	if (l->line)
		ft_putstr(l->line);
	apply_termcap_str("cm", l->pmpt, len_pmpt / l->co + 1);
	g_shell.signal_indicator = 0;
}

static void		sig_winch_handler(int sig)
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

void sig_controller(int option)
{
	if (option == PARENT)
	{
		signal (SIGSTOP, SIG_IGN);
    	signal (SIGTSTP, SIG_IGN);
    	signal (SIGTTIN, SIG_IGN);
    	signal (SIGTTOU, SIG_IGN);
    	signal (SIGCHLD, SIG_DFL);
		signal(SIGPIPE, SIG_IGN);
    	// signal (SIGCHLD, SIG_IGN);
		signal(SIGINT, sig_int_handler);
		signal(SIGWINCH, sig_winch_handler);
	}
	else if (option == CHILD)
	{
		// for debug
		int i;
		i = 1;
		while (i < 32)
		{
			signal(i, SIG_DFL);
			i++;
		}
	}
}
