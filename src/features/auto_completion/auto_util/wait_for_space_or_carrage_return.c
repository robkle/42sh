/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait_for_space_or_carrage_return.c                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihwang <ihwang@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/21 14:04:02 by ihwang            #+#    #+#             */
/*   Updated: 2021/03/21 14:58:44 by ihwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void		wait_for_space_or_carrage_return(char buf[])
{
	ft_putstr("--More--");
	auto_read_input("\n q", buf);
}
