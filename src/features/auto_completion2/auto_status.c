/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   auto_status.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthan <dthan@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/23 21:26:59 by marvin            #+#    #+#             */
/*   Updated: 2020/12/27 17:49:57 by dthan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void        set_status_new_pos(long *status)
{
    *status |= AUTO_STAT_NEW_POS;
}

void        set_status_over_term_size(long *status)
{
    *status |= AUTO_STAT_OVER_TERM_SIZE;
}

void        set_status_completed(long *status)
{
    *status |= AUTO_STAT_COMPLETED;
}

void        set_status_dir(long *status)
{
    *status |= AUTO_STAT_DIR;
}

void        set_status_list(long *status)
{
    *status |= AUTO_STAT_LIST;
}

void        delete_status_new_pos(long *status)
{
    *status &= ~AUTO_STAT_NEW_POS;
}

void        delete_status_dir(long *status)
{
    *status &= ~AUTO_STAT_DIR;
}

void        delete_status_completed(long *status)
{
    *status &= ~AUTO_STAT_COMPLETED;
}

void        delete_status_over_term_size(long *status)
{
    *status &= ~AUTO_STAT_OVER_TERM_SIZE;
}