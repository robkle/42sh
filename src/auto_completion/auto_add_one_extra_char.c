/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   auto_add_one_extra_char.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihwang <ihwang@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/14 22:29:50 by marvin            #+#    #+#             */
/*   Updated: 2020/10/14 22:30:10 by ihwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "add_key.h"

void		auto_add_one_extra_char(t_l *l)
{
	char	buf_for_addkey[2];

	ft_memset(buf_for_addkey, 0, sizeof(buf_for_addkey));
	buf_for_addkey[0] = ' ';
	add_key(buf_for_addkey, l);
}
