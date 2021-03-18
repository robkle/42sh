/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history_input_check.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthan <dthan@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/21 10:55:32 by rklein            #+#    #+#             */
/*   Updated: 2021/03/18 07:52:38 by rklein           ###   ########.fr       */
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

/*

open file
int end_pos = 0;
get nextline until get_next_line == -1
contain the line in the buffer[4096];
first ft_bzero(buffer, 4096);
while (get_line_buffer(single_line))
{
	ft_strcat(buffer, single_line);
	if ((end_pos = analyzing_the_buffer(&in_quotation)) != -1) --> means add buffer to history line
	{
		history[i] = ft_strndup(buffer, end_pos + 1);
		..... history thing here
		ft_strcpy(buffer, &buffer[end_pos + 1]);
	}
	else
		ft_strcpy(buffer, "\n");
}

------
what it will return:
	1. return end_pos of the buffer:
		a, if there is EOF
			+ if EOF 
		b, there is no EOF
int analyzing_the_buffer(char [4096]buffer)
{
	int i = -1;

	while (buffer[++i])
	{
		if (buffer[i] == 4) --> EOF character
			return (i);
		if (is_in_hibitor() == 1)
		{
			if (jump_quote() == EXIT_FAILURE))
				return (-1);
		}
		else if ( && and || and | )
			return (-1);
	}
	return (i == 0) ? -1 : i - 1;
}


*/

int			ft_check_cont(char buf[])
{
	int	i;
	int	ch;

	ch = 0;
	i = -1;
	while (buf[++i])
	{
		if (buf[i] == 4)
			return (i);
		if (is_inhibitors(&buf[i], i, buf[i]))
		{
			if (jump_quote(&buf[i], &i, buf[i]) == EXIT_FAILURE)
				return(-1);
		}
		else if (ft_strnequ(&buf[i], "&&", 2) || ft_strnequ(&buf[i], "||", 2))
		{
			ch = ch ? 0 : 1;
			i++;
		}
		else if (buf[i] == '|')
			ch = ch ? 0 : 1;
		else if (ch && !ft_isspace(buf[i]))
			ch =  0;
	}
	return (i == 0 || ch == 1 ? -1 : i - 1);
}
	
/*int			hist_quote_jump(char *input, int *i, char qt)
{
	*i += 1;
	while (input[*i])
	{
		if (input[*i] == qt && is_real_character(input, *i))
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
	if (buffer[ft_strlen(buffer) - 1] == 4)
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
}*/

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
