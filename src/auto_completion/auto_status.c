/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   auto_status.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihwang <ihwang@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/23 21:26:59 by marvin            #+#    #+#             */
/*   Updated: 2020/09/29 20:05:37 by ihwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "auto_completion.h"

void        set_status_new_pos(long *status)
{
    *status |= AUTO_STAT_NEW_POS;
}

void        set_status_open(long *status)
{
    *status |= AUTO_STAT_OPEN;
}

void        set_status_word_in_path(long *status)
{
    *status |= AUTO_STAT_WORD_IN_PATH;
}

void        set_status_other_possibility(long *status)
{
    *status |= AUTO_STAT_OTHER_POSSIBILITY;
}

void        set_status_completed(long *status)
{
    *status |= AUTO_STAT_COMPLETED;
}

void        set_status_dir(long *status)
{
    *status |= AUTO_STAT_DIR;
}

void        set_status_typed_upto(long *status)
{
    *status |= AUTO_STAT_TYPED_UPTO;
}

void        set_status_list(long *status)
{
    *status |= AUTO_STAT_LIST;
}

void        set_status_perm(long *status)
{
    *status |= AUTO_STAT_PERM;
}

void        set_status_root(long *status)
{
    *status |= AUTO_STAT_ROOT;
}

void        delete_status_new_pos(long *status)
{
    *status &= ~AUTO_STAT_NEW_POS;
}

void        delete_status_dir(long *status)
{
    *status &= ~AUTO_STAT_DIR;
}
