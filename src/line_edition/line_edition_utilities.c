/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_edition_utilities.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihwang <ihwang@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/26 21:28:25 by marvin            #+#    #+#             */
/*   Updated: 2020/09/26 21:32:01 by ihwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "line_edition_utilities.h"

void				apply_termcap_str(char *str, int x, int y)
{
	if (!ft_strcmp(str, "ch") || !ft_strcmp(str, "cm"))
		tputs(tgoto(tgetstr(str, NULL), x, y), 1, ft_putchar);
	else
		tputs(tgetstr(str, NULL), 1, ft_putchar);
}

size_t				get_current_row(void)
{
	int				fd_tty;
	char			answer[16];
	size_t			answerlen;

	fd_tty = open("/dev/tty", O_RDWR);
	write(fd_tty, "\x1B[6n", 4);
	ft_memset(answer, 0, sizeof(answer));
	answerlen = 0;
	while ((read(fd_tty, answer + answerlen, 1)) == 1)
	{
		if (answer[answerlen++] == 'R')
			break ;
	}
	answer[answerlen] = '\0';
	close(fd_tty);
	return (ft_atoi(&answer[2]));
}

size_t				get_current_column(void)
{
	int				fd_tty;
	char			answer[16];
	size_t			answerlen;
	int				row;
	int				column;

	fd_tty = open("/dev/tty", O_RDWR);
	write(fd_tty, "\x1B[6n", 4);
	ft_memset(answer, 0, sizeof(answer));
	answerlen = 0;
	while ((read(fd_tty, answer + answerlen, 1)) == 1)
	{
		if (answer[answerlen++] == 'R')
			break ;
	}
	answer[answerlen] = '\0';
	close(fd_tty);
	row = ft_atoi(&answer[2]);
	if (ft_nbrlen(row) == 1)
		column = ft_atoi(&answer[4]);
	else
		column = ft_atoi(&answer[5]);
	return (column);
}