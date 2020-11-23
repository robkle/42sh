/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type_u.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthan <dthan@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/23 08:01:44 by dthan             #+#    #+#             */
/*   Updated: 2020/10/10 02:09:15 by dthan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_printf.h"

void	type_u(t_info *info, va_list arg, size_t *ct, int fd)
{
	unsigned long long	num;
	char				*str;

	num = get_unsigned_argument(info, arg);
	str = ft_itoa_unsigned_longlong(num);
	flag_ignore(info, str);
	prec_ctrl_nums(info, &str, 0);
	flag_control(info, &str, 0);
	width_ctrl(info, &str);
	write(fd, str, *ct = ft_strlen(str));
	free(str);
}
