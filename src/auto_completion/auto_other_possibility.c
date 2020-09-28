/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   auto_other_possibility.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihwang <ihwang@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/27 13:59:10 by marvin            #+#    #+#             */
/*   Updated: 2020/09/27 13:59:31 by ihwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "auto_completion.h"

char        is_typed_upto(t_l *l)
{

}

void        auto_other_possibility(t_l *l)
{
    if (is_typed_upto(l))
        auto_typed_upto(l);
    else
        auto_fulfill_upto(l);
}
