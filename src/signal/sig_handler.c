/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig_handler.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthan <dthan@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/04 17:21:07 by ihwang            #+#    #+#             */
/*   Updated: 2020/10/16 14:57:23 by dthan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void post_signal(t_l *l)
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
	g_prompt = 0;
}

static void sig_int_handler(int sig)
{
	(void)sig;
	g_prompt = 1;
	ioctl(1, TIOCSTI, "");
}

/*
static void sig_tstp_handler(int sig)
{
	(void)sig;
	g_prompt = 1;
	ioctl(1, TIOCSTI, "");
}
*/

void sig_controller(int option)
{
	if (option == PARENT)
	{
    	// signal (SIGINT, SIG_IGN);
    	signal (SIGQUIT, SIG_IGN);
		signal (SIGSTOP, SIG_IGN);
    	signal (SIGTSTP, SIG_IGN);
    	signal (SIGTTIN, SIG_IGN);
    	signal (SIGTTOU, SIG_IGN);
    	// signal (SIGCHLD, SIG_IGN);
		signal(SIGINT, sig_int_handler);
	}
	else if (option == CHILD)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		signal(SIGTSTP, SIG_DFL);
		signal(SIGTTIN, SIG_DFL);
		signal(SIGTTOU, SIG_DFL);
		signal(SIGCHLD, SIG_DFL);
		int i;

		i = 1;
		while (i < 32)
		{
			signal(i, SIG_DFL);
			i++;
		}
	}
}
