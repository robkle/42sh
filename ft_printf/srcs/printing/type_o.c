/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type_o.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthan <dthan@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/23 08:51:30 by dthan             #+#    #+#             */
/*   Updated: 2020/12/26 19:09:26 by dthan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_printf.h"
#define OCTAL_MASK 7
#define SHIFF_OCTAL_MASK 3

void	type_o(t_info *info, va_list arg, size_t *ct, int fd)
{
	unsigned long long	num;
	char				*str;
	char				*oct;

	oct = "01234567";
	num = get_unsigned_argument(info, arg);
	str = ft_number_conversion(num, OCTAL_MASK, SHIFF_OCTAL_MASK, oct);
	flag_ignore(info, str);
	prec_ctrl_oct_hex(info, &str);
	flag_control(info, &str, 0);
	width_ctrl(info, &str);
	write(fd, str, *ct = ft_strlen(str));
	free(str);
}
