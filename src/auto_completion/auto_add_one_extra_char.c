/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   auto_add_one_extra_char.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihwang <ihwang@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/14 22:29:50 by marvin            #+#    #+#             */
/*   Updated: 2020/10/16 22:52:33 by ihwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "add_key.h"

void		auto_add_one_extra_char(t_l *l, char c)
{
	char	buf_for_addkey[2];

	ft_memset(buf_for_addkey, 0, sizeof(buf_for_addkey));
	buf_for_addkey[0] = c;
	add_key(buf_for_addkey, l);
}
