/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hex_value.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthan <dthan@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/30 14:07:13 by dthan             #+#    #+#             */
/*   Updated: 2020/12/30 14:45:50 by dthan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int is_eight_bit_character_whose_value_is_hexadecimal_value(char *str)
{
	if (!str[0] || !str[1] || !str[2])
		return (0);
	if (str[0] != 'x')
		return (0);
	if (!ft_isdigit(str[1]) || (str[1] < '0' && str[1] > '7'))
		return (0);
	if (!ft_isdigit(str[2]) && str[2] < 'A' && str[2] > 'F')
		return (0);
	return (1);
}

int convert_hex_to_decimal(char *str)
{
	int base = 1;
	int decimal = 0;
	int i = ft_strlen(str);

	while (--i >= 0)
	{
		if (str[i] >= '0' && str[i] <= '9')
			decimal += (str[i] - 48) * base; 
		else if (str[i] >= 'A' && str[i] <= 'F')
			decimal += (str[i] - 55) * base;
		base = base * 16;
	}
	return (decimal);
}

char replace_hex_value(char *str)
{
	char chars[3];
	
	chars[0] = str[0];
	chars[1] = str[1];
	chars[2] = '\0';
	return (convert_hex_to_decimal(chars));
}
