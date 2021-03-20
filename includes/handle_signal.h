/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_signal.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthan <dthan@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/18 20:29:42 by marvin            #+#    #+#             */
/*   Updated: 2021/03/20 16:38:49 by dthan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HANDLE_SIGNAL_H
# define HANDLE_SIGNAL_H
# include "struct.h"

# define SIGNAL_NUMBER_OSX 31

# define SIGHUP_MSG "Hangup"
# define SIGINT_MSG "Interrupt"
# define SIGQUIT_MSG "Quit"
# define SIGILL_MSG "Illegal instruction"
# define SIGTRAP_MSG "Trace/BPT trap"
# define SIGABRT_MSG "Abort trap"
# define SIGEMT_MSG "EMT trap"
# define SIGFPE_MSG "Floating point exception"
# define SIGKILL_MSG "Killed"
# define SIGBUS_MSG "Bus error"
# define SIGSEGV_MSG "Segmentation fault"
# define SIGSYS_MSG "Bad system call"
# define SIGPIPE_MSG "SIGPIPE sent"
# define SIGALRM_MSG "Alarm clock"
# define SIGTERM_MSG "Terminated"
# define SIGURG_MSG  "SIGURG sent"
# define SIGSTOP_MSG "SIGSTOP sent"
# define SIGTSTP_MSG "SIGTSTP sent"
# define SIGCONT_MSG "SIGCONT sent"
# define SIGCHLD_MSG "SIGCHLD sent"
# define SIGTTIN_MSG "SIGTTIN sent"
# define SIGTTOU_MSG "SIGTTOU sent"
# define SIGIO_MSG "SIGIO sent"
# define SIGXCPU_MSG "Cputime limit exceeded"
# define SIGXFSZ_MSG "SIGXFSZ sent"
# define SIGVTALRM_MSG "Virtual timer expired"
# define SIGPROF_MSG "Profiling timer expired"
# define SIGWINCH_MSG "SIGWINCH sent"
# define SIGINFO_MSG "SIGINFO sent"
# define SIGUSR1_MSG "User defined signal 1"
# define SIGUSR2_MSG "User defined signal 2"

void	sig_controller(int option);
void	init_signal_messages(char *sig_msgs[SIGNAL_NUMBER_OSX]);
void	sig_int_handler(int sig);
void	handle_sigwinch(t_l *l);
char	is_signal_should_print(int sig);

#endif
