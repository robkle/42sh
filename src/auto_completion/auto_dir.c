/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   auto_dir.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihwang <ihwang@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/27 13:47:07 by marvin            #+#    #+#             */
/*   Updated: 2020/10/01 14:21:23 by ihwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "auto_completion.h"


void        auto_dir(t_l *l)
{
    if (auto_is_dir(l->auto_com.full_path, l->auto_com.target_str))
    {
        set_status_dir(&l->auto_com.status);
        auto_ready_to_print(l);
    }
}
