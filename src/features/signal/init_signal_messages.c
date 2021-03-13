/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_signal_messages.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthan <dthan@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/09 16:49:44 by tango             #+#    #+#             */
/*   Updated: 2021/03/13 23:19:25 by dthan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <shell.h>

// static void init_signal_messages2(void)
// {
// 	ft_strcpy(g_shell.sig_msgs[16], SIGSTOP_MSG);
// 	ft_strcpy(g_shell.sig_msgs[17], SIGTSTP_MSG);
// 	ft_strcpy(g_shell.sig_msgs[18], SIGCONT_MSG);
// 	ft_strcpy(g_shell.sig_msgs[19], SIGCHLD_MSG);
// 	ft_strcpy(g_shell.sig_msgs[20], SIGTTIN_MSG);
// 	ft_strcpy(g_shell.sig_msgs[21], SIGTTOU_MSG);
// 	ft_strcpy(g_shell.sig_msgs[22], SIGIO_MSG);
// 	ft_strcpy(g_shell.sig_msgs[23], SIGXCPU_MSG);
// 	ft_strcpy(g_shell.sig_msgs[24], SIGXFSZ_MSG);
// 	ft_strcpy(g_shell.sig_msgs[25], SIGVTALRM_MSG);
// 	ft_strcpy(g_shell.sig_msgs[26], SIGPROF_MSG);
// 	ft_strcpy(g_shell.sig_msgs[27], SIGWINCH_MSG);
// 	ft_strcpy(g_shell.sig_msgs[28], SIGINFO_MSG);
// 	ft_strcpy(g_shell.sig_msgs[29], SIGUSR1_MSG);
// 	ft_strcpy(g_shell.sig_msgs[30], SIGUSR2_MSG);
// }

// void init_signal_messages(void)
// {
// 	ft_strcpy(g_shell.sig_msgs[0], SIGHUP_MSG);
// 	ft_strcpy(g_shell.sig_msgs[1], SIGINT_MSG);
// 	ft_strcpy(g_shell.sig_msgs[2], SIGQUIT_MSG);
// 	ft_strcpy(g_shell.sig_msgs[3], SIGILL_MSG);
// 	ft_strcpy(g_shell.sig_msgs[4], SIGTRAP_MSG);
// 	ft_strcpy(g_shell.sig_msgs[5], SIGABRT_MSG);
// 	ft_strcpy(g_shell.sig_msgs[6], SIGEMT_MSG);
// 	ft_strcpy(g_shell.sig_msgs[7], SIGFPE_MSG);
// 	ft_strcpy(g_shell.sig_msgs[8], SIGKILL_MSG);
// 	ft_strcpy(g_shell.sig_msgs[9], SIGBUS_MSG);
// 	ft_strcpy(g_shell.sig_msgs[10], SIGSEGV_MSG);
// 	ft_strcpy(g_shell.sig_msgs[11], SIGSYS_MSG);
// 	ft_strcpy(g_shell.sig_msgs[12], SIGPIPE_MSG);
// 	ft_strcpy(g_shell.sig_msgs[13], SIGALRM_MSG);
// 	ft_strcpy(g_shell.sig_msgs[14], SIGTERM_MSG);
// 	ft_strcpy(g_shell.sig_msgs[15], SIGURG_MSG);
// 	return (init_signal_messages2());
// }

static void init_signal_messages2(char *sig_msgs[SIGNAL_NUMBER_OSX])
{
	sig_msgs[16] = SIGSTOP_MSG;
	sig_msgs[17] = SIGTSTP_MSG;
	sig_msgs[18] = SIGCONT_MSG;
	sig_msgs[19] = SIGCHLD_MSG;
	sig_msgs[20] = SIGTTIN_MSG;
	sig_msgs[21] = SIGTTOU_MSG;
	sig_msgs[22] = SIGIO_MSG;
	sig_msgs[23] = SIGXCPU_MSG;
	sig_msgs[24] = SIGXFSZ_MSG;
	sig_msgs[25] = SIGVTALRM_MSG;
	sig_msgs[26] = SIGPROF_MSG;
	sig_msgs[27] = SIGWINCH_MSG;
	sig_msgs[28] = SIGINFO_MSG;
	sig_msgs[29] = SIGUSR1_MSG;
	sig_msgs[30] = SIGUSR2_MSG;
}

void init_signal_messages(char *sig_msgs[SIGNAL_NUMBER_OSX])
{
	ft_printf("here\n");
	sig_msgs[0] = SIGHUP_MSG;
	sig_msgs[1] = SIGINT_MSG;
	sig_msgs[2] = SIGQUIT_MSG;
	sig_msgs[3] = SIGILL_MSG;
	sig_msgs[4] = SIGTRAP_MSG;
	sig_msgs[5] = SIGABRT_MSG;
	sig_msgs[6] = SIGEMT_MSG;
	sig_msgs[7] = SIGFPE_MSG;
	sig_msgs[8] = SIGKILL_MSG;
	sig_msgs[9] = SIGBUS_MSG;
	sig_msgs[10] = SIGSEGV_MSG;
	sig_msgs[11] = SIGSYS_MSG;
	sig_msgs[12] = SIGPIPE_MSG;
	sig_msgs[13] = SIGALRM_MSG;
	sig_msgs[14] = SIGTERM_MSG;
	sig_msgs[15] = SIGURG_MSG;
	return (init_signal_messages2(sig_msgs));
}

