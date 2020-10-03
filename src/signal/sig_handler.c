/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig_handler.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihwang <ihwang@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/04 17:21:07 by ihwang            #+#    #+#             */
/*   Updated: 2020/10/03 19:56:18 by ihwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "line_edition_utilities.h"

void			post_sigint(t_l *l)
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
	g_signal_indicator &= ~SIGINT_INDICATOR;
}

void			post_sigwinch(t_l *l)
{
	apply_termcap_str("cl", 0, 0);
	get_prompt();
	l->co = tgetnum("co");
	l->total_row = tgetnum("li");
	l->starting_row = l->total_row - get_current_row();
	l->x = l->pmpt;
	l->y = 0;
	if (l->line)
		ft_putstr(l->line);
	apply_termcap_str("cm", l->pmpt, 1);
	g_signal_indicator &= ~SIGWINCH_INDICATOR;
}

static	void	sig_int_handler(int sig)
{
	(void)sig;
	g_signal_indicator |= SIGINT_INDICATOR;
	ioctl(1, TIOCSTI, "");
}

static	void	sig_tstp_handler(int sig)
{
	(void)sig;
}

static void		sig_winch_handler(int sig)
{
	(void)sig;
	g_signal_indicator |= SIGWINCH_INDICATOR;
	if (!(tgetent(NULL, getenv("TERM"))))
	{
		ft_putstr_fd("Environment variable 'TERM' not set \n", 2);
		ft_exit(EXIT_FAILURE);
	}
	ioctl(1, TIOCSTI, "");
}

void			sig_controller(int option)
{
	if (option == PARENT)
	{
		signal(SIGINT, sig_int_handler);
		signal(SIGTSTP, sig_tstp_handler);
		signal(SIGWINCH, sig_winch_handler);
	}
	else if (option == CHILD)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGTSTP, SIG_DFL);
		signal(SIGWINCH, SIG_DFL);
	}
}
