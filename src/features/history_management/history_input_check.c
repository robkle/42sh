/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history_input_check.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthan <dthan@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/21 10:55:32 by rklein            #+#    #+#             */
/*   Updated: 2020/12/25 17:45:55 by dthan            ###   ########.fr       */
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
		if (buffer[i] == '\'' && buffer[i - 1] != '\\')
			ch = ft_quotes(ch, 1);
		else if (buffer[i] == '"' && buffer[i - 1] != '\\')
			ch = ft_quotes(ch, 2);
		else if (buffer[i] == '|' && buffer[i - 1] != '\\' && \
			buffer[i - 1] != '|' && ch == 0)
			ch += 4;
		else if ((buffer[i] != '|' || \
			(buffer[i] == '|' && buffer[i - 1] == '|')) && \
			buffer[i] != ' ' && ch == 4)
			ch -= 4;
	}
	return (ch);
}
