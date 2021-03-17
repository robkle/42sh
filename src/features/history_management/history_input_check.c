/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history_input_check.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthan <dthan@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/21 10:55:32 by rklein            #+#    #+#             */
/*   Updated: 2021/03/17 16:48:52 by rklein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

/*static int	ft_quotes(int ch, int q)
{
	if (!(ch % 4))
		ch += q;
	else if (ch % 4 == q)
		ch -= q;
	return (ch);
}*/

int			hist_quote_jump(char *input, int *i, char qt)
{
	ft_printf("[%d]", *i);//TEST
	*i += 1;

	while (input[*i])
	{
		if (input[*i] == qt && input[*i - 1] != '\\')
			break;
		*i += 1;
	}
	if (input[*i] == '\0')
		return (1);
	return (0);
}

int			ft_check_cont(char *buffer)
{
	int	i;
	int	ch;

	ch = 0;
	i = -1;
	if (buffer[ft_strlen(buffer) - 2] == 4)
		return (0);
	while (buffer[++i])
	{
		if ((buffer[i] == '\'' || buffer[i] == '"') && (i == 0 || \
		buffer[i - 1] != '\\'))
		{
			ch = hist_quote_jump(&buffer[i], &i, buffer[i]);
			if (buffer[i] == '\0')
				break;
		}
		else if (ft_strnequ(&buffer[i], "&&", 2) || \
		ft_strnequ(&buffer[i], "||", 2))
		{
			ch = ch ? 0 : 1;
			i++;
		}
		else if (buffer[i] == '|')
			ch = ch ? 0 : 1;
		else if (ch && !ft_isspace(buffer[i]))
			ch = ch ? 0 : 1;
	}
	return (ch);
}

/*int			ft_check_cont(char *buffer)
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
}*/
