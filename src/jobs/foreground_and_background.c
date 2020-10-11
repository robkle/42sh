/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   foreground_and_background.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthan <dthan@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/02 02:28:34 by dthan             #+#    #+#             */
/*   Updated: 2020/10/08 02:34:01 by dthan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/shell.h"

// int put_job_in_foreground(t_job *job, int cont)
// {
// 	int ret;

// 	tcsetpgrp(STDIN_FILENO, job->pgid);
// 	if (cont)
// 	{
// 		tcsetattr(STDIN_FILENO, TCSADRAIN, &job->term);
// 		if (kill(- job->pgid, SIGCONT) < 0)
// 			perror("kill (SIGCONT)"); //error management here
// 	}
// 	ret = wait_for_job(job, WUNTRACED);
// 	tcsetpgrp(STDIN_FILENO, g_shell.shell_pgid);
// 	tcgetattr(STDIN_FILENO, &job->term);
// 	tcsetattr(STDIN_FILENO, TCSADRAIN, &g_shell.shell_tmode);
// 	return (ret);
// }

void put_job_in_foreground(t_job *job, int cont)
{
	tcsetpgrp(STDIN_FILENO, job->pgid);
	if (cont)
	{
		tcsetattr(STDIN_FILENO, TCSADRAIN, &job->term);
		if (kill(- job->pgid, SIGCONT) < 0)
			perror("kill (SIGCONT)"); //error management here
	}
	wait_for_job(job);
	// signal(SIGTTOU, SIG_IGN);
	tcsetpgrp(STDIN_FILENO, g_shell.shell_pgid);
	// signal(SIGTTOU, SIG_DFL);
	tcgetattr(STDIN_FILENO, &job->term);
	tcsetattr(STDIN_FILENO, TCSADRAIN, &g_shell.shell_tmode);
}

// int put_job_in_background(t_job *job, int cont)
// {
// 	if (cont)
// 		if (kill(-job->pgid, SIGCONT) < 0)
// 			perror("kill (SIGCONT)");
// 	return (EXIT_SUCCESS);
// }

void put_job_in_background(t_job *job, int cont)
{
	if (cont)
		if (kill(-job->pgid, SIGCONT) < 0)
			perror("kill (SIGCONT)");
}
