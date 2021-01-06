/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   auto_add_one_extra_char.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthan <dthan@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/14 22:29:50 by marvin            #+#    #+#             */
/*   Updated: 2020/12/27 17:51:16 by dthan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void		auto_add_one_extra_char(t_l *editor, char c)
{
	char	buf_for_addkey[2];

	ft_memset(buf_for_addkey, 0, sizeof(buf_for_addkey));
	buf_for_addkey[0] = c;
	add_key(buf_for_addkey, editor);
}
