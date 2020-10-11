
#include "shell.h"

int	ft_fg(void)
{
	int pgid;
	t_job* j;
	// t_process *p;

	j = (t_job*)(g_shell.first_job->content);
	// p = (t_process*)(j->process->content);
	pgid = j->pgid;
	kill(-pgid, SIGCONT);

	ft_tcsetpgrp(STDIN_FILENO, pgid);
	wait_for_job(j);
	

	ft_tcsetpgrp(STDIN_FILENO, g_shell.shell_pgid);

	return (EXIT_SUCCESS);
}