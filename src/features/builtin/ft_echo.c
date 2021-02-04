/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihwang <ihwang@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/14 10:23:54 by dthan             #+#    #+#             */
/*   Updated: 2021/02/04 15:48:25 by ihwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static int	apply_option(char *operand, int *opt_n_flag)
{
	int		i;

	i = 1;
	while (operand[i] == 'n')
		i++;
	if (operand[i] == '\0')
	{
		*opt_n_flag = 1;
		return (FALSE);
	}
	return (TRUE);
}

int			ft_echo(t_process *p)
{
	int		i;
	int		is_opt_n;
	int		is_stop;

	i = 0;
	is_opt_n = FALSE;
	is_stop = FALSE;
	while (is_stop == FALSE && ++i < p->ac && \
		p->av[i][0] == '-' && ft_strlen(p->av[i]) > 1)
		is_stop = apply_option(p->av[i], &is_opt_n);
	while (i < p->ac)
	{
		ft_putstr(p->av[i]);
		if (i + 1 != p->ac && ft_strcmp(p->av[i], ""))
			ft_putstr(" ");
		i++;
	}
	if (is_opt_n == FALSE)
		ft_putchar('\n');
	return (EXIT_SUCCESS);
}
