/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc_unary.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/29 20:10:24 by marvin            #+#    #+#             */
/*   Updated: 2021/03/29 20:15:37 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	ft_calc_unary(t_st *stack)
{
	char	*calc;
	char	*tmp;

	calc = ft_llitoa(-1 * (ft_atolli(stack->op)));
	tmp = stack->op;
	stack->op = calc;
	free(tmp);
}
