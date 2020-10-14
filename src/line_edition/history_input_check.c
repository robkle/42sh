/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   qph_check.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rklein <rklein@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/21 10:55:32 by rklein            #+#    #+#             */
/*   Updated: 2020/09/25 15:13:48 by rklein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static int	ft_quotes(int ch, int q)
{
	if (!(ch % 4))
		ch += q;
	else if (ch % 4 == q)
		ch -= q;
	return (ch);
}

int		ft_check_cont(char *buffer)
{
	int	i;
	int	ch;
		
	ch = 0;
	i = -1;
	while (buffer[++i])
	{
		if (buffer[i] == 39 && buffer[i - 1] != 92)
			ch = ft_quotes(ch, 1);
		if (buffer[i] == 34 && buffer[i - 1] != 92)
			ch = ft_quotes(ch, 2);
		if (buffer[i] == 124 && buffer[i - 1] != 92 &&
				buffer[i - 1] != 124 && !ch)
			ch += 4;
		if ((buffer[i] != 124 || (buffer[i] == 124 && buffer[i - 1] == 124))
				&& buffer[i] != ' ' && ch == 4)
			ch -= 4;
	}
	return (ch);
}
