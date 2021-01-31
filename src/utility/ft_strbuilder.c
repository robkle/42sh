/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strbuilder.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthan <dthan@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/25 18:10:12 by dthan             #+#    #+#             */
/*   Updated: 2021/01/28 16:20:03 by dthan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

char	*ft_strbuilder(int argc, char *str, ...)
{
	va_list	ap;
	int		i;

	i = 0;
	va_start(ap, str);
	while (i++ < argc)
		str = ft_strjoin_and_free_string1(str, va_arg(ap, char*));
	va_end(ap);
	return (str);
}
