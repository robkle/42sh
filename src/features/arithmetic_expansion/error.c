/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rklein <rklein@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/01 10:44:20 by rklein            #+#    #+#             */
/*   Updated: 2021/02/15 18:09:44 by rklein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static void	ft_print_arx_token(t_st *lst)
{
	while (lst)
	{
		if (ft_strequ(lst->type, "operator") && \
		(lst->op[0] == 'p' || lst->op[0] == 's' || lst->op[0] == 'u'))
			ft_putstr(&lst->op[1]);
		else
			ft_putstr(lst->op);
		lst = lst->next;
	}
}

void		ft_print_error(int error, t_st *infix, t_st *expr)
{
	write(1, "42sh: ", 6);
	ft_print_arx_token(expr);
	if (error == INVOP)
		write(1, ": syntax error: invalid arithmetic operator ", 44);
	if (error == VTGFB)
		write(1, ": value too great for base ", 27);
	if (error == OPEXP)
		write(1, ": syntax error: operand expected ", 34);
	if (error == INVBA)
		write(1, ": invalid arithmetic base ", 26);
	if (error == INVNU)
		write(1, ": invalid number ", 17);
	if (error == SNERR)
		write(1, ": syntax error in expression ", 28);
	write(1, "(error token is \"", 17);
	ft_print_arx_token(infix);
	write(1, "\")\n", 3);
	ft_free_lst(&expr);
}
