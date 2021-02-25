/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_redirect.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthan <dthan@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/02 02:26:01 by tango             #+#    #+#             */
/*   Updated: 2021/02/24 12:04:47 by dthan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	set_stdin_stdout_stderr_channels(int old[3])
{
	if (old[STDIN_FILENO] != STDIN_FILENO)
	{
		dup2(old[STDIN_FILENO], STDIN_FILENO);
		close(old[STDIN_FILENO]);
	}
	if (old[STDOUT_FILENO] != STDOUT_FILENO)
	{
		dup2(old[STDOUT_FILENO], STDOUT_FILENO);
		close(old[STDOUT_FILENO]);
	}
	if (old[STDERR_FILENO] != STDERR_FILENO)
	{
		dup2(old[STDERR_FILENO], STDERR_FILENO);
		close(old[STDERR_FILENO]);
	}
}

void	reset_stdin_stdout_stderr_channels(int saved[3])
{
	dup2(saved[STDIN_FILENO], STDIN_FILENO);
	close(saved[STDIN_FILENO]);
	dup2(saved[STDOUT_FILENO], STDOUT_FILENO);
	close(saved[STDOUT_FILENO]);
	dup2(saved[STDERR_FILENO], STDERR_FILENO);
	close(saved[STDERR_FILENO]);
}

int		handle_redirection(t_process *p)
{
	t_redi	*redi_ptr;
	int		ret;

	if (p->first_redi == NULL)
		return (EXIT_SUCCESS);
	redi_ptr = p->first_redi;
	ret = EXIT_SUCCESS;
	while (redi_ptr && ret == EXIT_SUCCESS)
	{
		if (ft_strequ(redi_ptr->op, ">"))
			ret = redirect_great(redi_ptr);
		else if (ft_strequ(redi_ptr->op, ">>"))
			ret = redirect_dgreat(redi_ptr);
		else if (ft_strequ(redi_ptr->op, ">&"))
			ret = redirect_greatand(redi_ptr);
		else if (ft_strequ(redi_ptr->op, "<"))
			ret = redirect_less(redi_ptr);
		else if (ft_strequ(redi_ptr->op, "<<"))
			ret = redirect_dless(redi_ptr);
		else if (ft_strequ(redi_ptr->op, "<&"))
			ret = redirect_lessand(redi_ptr);
		redi_ptr = redi_ptr->next;
	}
	return (ret);
}
