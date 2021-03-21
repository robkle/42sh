/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   auto_delete_status.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihwang <ihwang@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/21 04:13:17 by ihwang            #+#    #+#             */
/*   Updated: 2021/03/21 04:14:19 by ihwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	delete_status_new_pos(long *status)
{
	*status &= ~AUTO_STAT_NEW_POS;
}

void	delete_status_dir(long *status)
{
	*status &= ~AUTO_STAT_DIR;
}

void	delete_status_completed(long *status)
{
	*status &= ~AUTO_STAT_COMPLETED;
}

void	delete_status_over_term_size(long *status)
{
	*status &= ~AUTO_STAT_OVER_TERM_SIZE;
}
