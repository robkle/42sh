/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   job_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthan <dthan@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/26 03:29:07 by dthan             #+#    #+#             */
/*   Updated: 2020/09/26 04:30:18 by dthan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/jobs.h"

t_job	*create_job(void)
{
	t_job *new;

	new = (t_job*)ft_memalloc(sizeof(t_job));
	new->command = NULL;
	new->pgid = 0;
	new->notified = 0;
	tcgetattr(STDIN_FILENO, &new->term);
	new->process = NULL;
	new->stdin = STDIN_FILENO;
	new->stdout = STDOUT_FILENO;
	new->stderr = STDERR_FILENO;
	new->foreground = 1;
	return new;
}
