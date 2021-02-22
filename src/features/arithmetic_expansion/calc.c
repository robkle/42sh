/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rklein <rklein@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/01 10:43:39 by rklein            #+#    #+#             */
/*   Updated: 2021/02/15 12:01:45 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static char	*ft_calculate(long long left, long long right, char *op)
{
	long long		res;

	res = 0;
	if (ft_strequ(op, "+"))
		res = left + right;
	else if (ft_strequ(op, "-"))
		res = left - right;
	else if (ft_strequ(op, "*"))
		res = left * right;
	else if (ft_strequ(op, "/"))
		res = left / right;
	else if (ft_strequ(op, "%"))
		res = left % right;
	else if (op[0] == '<')
		res = op[1] == '=' ? left <= right : left < right;
	else if (op[0] == '>')
		res = op[1] == '=' ? left >= right : left > right;
	else if (op[1] == '=')
		res = op[0] == '=' ? left == right : left != right;
	else if (ft_strequ(op, "&&"))
		res = left && right;
	else if (ft_strequ(op, "||"))
		res = left || right;
	return (ft_llitoa(res));
}

static void	ft_calc_pop(t_st **stack, char *op)
{
	long long	top;
	char		*tmp;

	if (ft_strequ((*stack)->type, "intvar"))
		ft_intvar(*stack, NULL);
	top = ft_atolli((*stack)->op);
	ft_pop_stack(stack);
	if (ft_strequ((*stack)->type, "intvar"))
		ft_intvar(*stack, NULL);
	tmp = ft_calculate(ft_atolli((*stack)->op), top, op);
	ft_modify_link(*stack, tmp, "integer");
	free(tmp);
}

long long	ft_calc(t_st *postfix)
{
	t_st		*stack;
	long long	top;

	stack = NULL;
	while (postfix)
	{
		if (!ft_strequ(postfix->type, "operator"))
			ft_push_stack(&stack, postfix->op, postfix->type);
		else if (ft_strequ(postfix->op, "u+") || ft_strequ(postfix->op, "u-"))
			stack->op = ft_strequ(postfix->op, "u-") ? \
			ft_llitoa(-1 * (ft_atolli(stack->op))) : stack->op;
		else if (ft_strequ(postfix->op, "p++") || \
		ft_strequ(postfix->op, "p--") || ft_strequ(postfix->op, "s++") || \
		ft_strequ(postfix->op, "s--"))
			ft_intvar(stack, postfix->op);
		else
			ft_calc_pop(&stack, postfix->op);
		postfix = postfix->next;
	}
	if (ft_strequ(stack->type, "intvar"))
		ft_intvar(stack, NULL);
	top = ft_atolli(stack->op);
	ft_free_lst(&stack);
	return (top);
}
