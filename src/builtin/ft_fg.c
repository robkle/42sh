
#include "shell.h"

int wake_bg_job_up(t_job *j)
{
	update_status();
	if (job_is_completed(j))
	{
		ft_printf("%s: fg: job has terminated\n", SHELL_NAME);
		return (EXIT_FAILURE);
	}
	ft_printf("%s\n", j->command);
	if (job_is_stopped(j))
		put_job_in_foreground(j, 1);
	else
		put_job_in_foreground(j, 0);
	j->foreground = 1;
	return (EXIT_SUCCESS);
}

int ft_fg_middle_man(t_job *current_j,int job_id)
{
	t_job *j;

	if (job_id == -1)
	{
		if ((j = find_the_last_job(current_j)) != NULL)
			return (wake_bg_job_up(j));
		ft_dprintf(2, "%s: fg: current: no such job\n", SHELL_NAME);
	}
	else
	{
		if ((j = find_job_with_id(job_id)) != NULL)
			return (wake_bg_job_up(j));
		ft_dprintf(2, "%s: fg: %d: no such job\n", SHELL_NAME, job_id);
	}
	return (EXIT_FAILURE);
}

int	ft_fg(t_job *j, t_process *p)
{
	int job_id;

	if (p->av[1] == NULL || ft_strequ(p->av[1], "%"))
		return (ft_fg_middle_man(j, -1));
	else if ((job_id = is_valid_job_id(j, p->av[1])) != 0)
		return (ft_fg_middle_man(j, job_id));
	ft_dprintf(2, "%s: fg: %s: no such job\n", SHELL_NAME, p->av[1]);
	return (EXIT_FAILURE);
}

int ft_fg_child()
{
	ft_dprintf(2, "%s: fg: no job control\n", SHELL_NAME);
	return (EXIT_FAILURE);
}
