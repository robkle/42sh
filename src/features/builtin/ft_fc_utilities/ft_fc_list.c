/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fc_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthan <dthan@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/23 18:11:36 by dthan             #+#    #+#             */
/*   Updated: 2021/03/13 22:46:37 by dthan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static void	fc_print(int *r_ind, int ops)
{
	int i;

	i = r_ind[0];
	if (r_ind[0] < r_ind[1])
		while (r_ind[0] < r_ind[1])
		{
			if (!(ops & FC_N_OP))
				ft_printf("%d", i++);
			ft_printf("\t%s\n", g_shell.history->hist[r_ind[0]++ - 1]);
		}
	else if (r_ind[0] > r_ind[1])
		while (r_ind[0] > r_ind[1])
		{
			if (!(ops & FC_N_OP))
				ft_printf("%d", i--);
			ft_printf("\t%s\n", g_shell.history->hist[r_ind[0]-- - 1]);
		}
	if (!(ops & FC_N_OP))
		ft_printf("%d", i++);
	ft_printf("\t%s\n", g_shell.history->hist[r_ind[0] - 1]);
}

static int	fc_list_init_range(int *r_ind, char *first, char *last)
{
	r_ind[0] = g_shell.history->curr;
	r_ind[1] = g_shell.history->curr;
	if (first)
	{
		r_ind[0] = fc_range(first);
		if (r_ind[0] == 0)
			return (fc_error_history_specification_out_of_range());
		r_ind[1] = r_ind[0];
		if (last)
		{
			r_ind[1] = fc_range(last);
			if (r_ind[1] == 0)
				return (fc_error_history_specification_out_of_range());
		}
	}
	else
	{
		if (r_ind[1] > 15)
			r_ind[0] = r_ind[1] - 15;
		else
			r_ind[0] = 1;
	}
	return (EXIT_SUCCESS);
}

int			fc_list(int ops, char *first, char *last)
{
	int	r_ind[2];

	if (fc_list_init_range(r_ind, first, last) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (ops & FC_R_OP)
		ft_swap_int(&r_ind[0], &r_ind[1]);
	fc_print(r_ind, ops);
	return (EXIT_SUCCESS);
}
