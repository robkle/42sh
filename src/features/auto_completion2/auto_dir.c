/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   auto_dir.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthan <dthan@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/27 13:47:07 by marvin            #+#    #+#             */
/*   Updated: 2020/12/27 17:48:53 by dthan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void        auto_dir(t_l *l)
{
    if (auto_is_dir(l->auto_com.full_path, l->auto_com.target_str))
    {
        set_status_dir(&l->auto_com.status);
        //auto_ready_to_print(l);
    }
}
