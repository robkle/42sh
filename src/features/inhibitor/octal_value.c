/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   octal_value.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthan <dthan@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/30 14:05:38 by dthan             #+#    #+#             */
/*   Updated: 2020/12/30 14:07:01 by dthan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static int is_octal_number(int num)
{
	int i;
	int minval;
	int maxval;

	i = -1;
	while (i++ < 18)
	{
		minval = i * 10;
		maxval = i * 10 + 7;
		if (num >= minval && num <= maxval)
			return (1);
	}
	return (0);
}

int is_eight_bit_character_whose_value_is_octal_value(char *str)
{
	char chars[4];
	int num;

	if (!str[0] || !str[1] || !str[2])
		return (0);
	if (!ft_isdigit(str[0]) || !ft_isdigit(str[1]) || !ft_isdigit(str[2]))
		return (0);
	chars[0] = str[0];
	chars[1] = str[1];
	chars[2] = str[2];
	chars[3] = '\0';
	num = ft_atoi(chars);
	if (is_octal_number(num))
		return (1);
	return (0);
}

static int convert_octal_to_decimal(int oct)
{
	int decimal = 0;
	int base = 1;
	int last_digit;

	while (oct)
	{
		last_digit = oct % 10;
		oct = oct / 10;
		decimal += last_digit * base;
		base = base * 8;
	}
	return (decimal);
}

char replace_octal_value(char *str)
{
	char chars[4];
	int num;

	chars[0] = str[0];
	chars[1] = str[1];
	chars[2] = str[2];
	chars[3] = '\0';
	num = ft_atoi(chars);
	return (convert_octal_to_decimal(num));
}
