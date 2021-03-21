/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihwang <ihwang@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/21 03:50:00 by ihwang            #+#    #+#             */
/*   Updated: 2021/03/21 03:50:30 by ihwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

void	ft_putnstr(char const *s, size_t len)
{
	size_t i;

	i = 0;
	while (s[i] && i < len)
	{
		write(STDOUT_FILENO, &s[i++], 1);
	}
}
