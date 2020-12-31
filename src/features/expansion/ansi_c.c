/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ansi_c.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthan <dthan@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/30 14:07:58 by dthan             #+#    #+#             */
/*   Updated: 2020/12/30 15:38:35 by dthan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int is_ansi_c_quoting(char *str)
{
	if (!str[0])
		return (0);
	if (str[0] == 'a' ||
		str[0] == 'b' ||
		str[0] == 'f' ||
		str[0] == 'n' ||
		str[0] == 'r' ||
		str[0] == 't' ||
		str[0] == 'v' ||
		str[0] == '\\')
		return (1);
	return (0);
}

char replace_ansi_c_quoting(char c)
{
	if (c == 'a')
		return ('\a');
	else if (c == 'b')
		return ('\b');
	else if (c == 'f')
		return ('\f');
	else if (c == 'n')
		return ('\n');
	else if (c == 'r')
		return ('\r');
	else if (c == 't')
		return ('\t');
	else if (c == 'v')
		return ('\v');
	else if (c == '\\')
		return ('\\');
	return ('\'');
}
