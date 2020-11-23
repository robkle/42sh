/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type_percent.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthan <dthan@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/06 21:35:36 by dthan             #+#    #+#             */
/*   Updated: 2020/10/10 02:09:15 by dthan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_printf.h"

void	type_percent(t_info *info, __attribute__((unused)) va_list arg, \
		size_t *ct, int fd)
{
	char percent;
	char *str;

	percent = '%';
	str = ft_strnew(1);
	str[0] = percent;
	width_ctrl(info, &str);
	write(fd, str, *ct = ft_strlen(str));
	free(str);
}
