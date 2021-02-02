/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   postfix.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rklein <rklein@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/01 10:54:56 by rklein            #+#    #+#             */
/*   Updated: 2021/02/01 12:27:49 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int			ft_operator_str(char *op)
{
	if (ft_strequ(op, "(") || ft_strequ(op, ")"))
		return (1);
	if (ft_strequ(op, "s++") || ft_strequ(op, "s--"))
		return (1);
	if (ft_strequ(op, "p++") || ft_strequ(op, "p--"))
		return (1);
	if (ft_strequ(op, "u+") || ft_strequ(op, "u-"))
		return (1);
	if (ft_strequ(op, "*") || ft_strequ(op, "/") || ft_strequ(op, "%"))
		return (1);
	if (ft_strequ(op, "+") || ft_strequ(op, "-"))
		return (1);
	if (ft_strequ(op, "<") || ft_strequ(op, ">"))
		return (1);
	if (ft_strequ(op, "<=") || ft_strequ(op, ">="))
		return (1);
	if (ft_strequ(op, "==") || ft_strequ(op, "!="))
		return (1);
	if (ft_strequ(op, "&&") || ft_strequ(op, "||"))
		return (1);
	return (0);
}

static t_pr	ft_pr_assign(char *op)
{
	if (ft_strequ(op, "s++") || ft_strequ(op, "s--"))
		return (SU);
	if (ft_strequ(op, "u+") || ft_strequ(op, "u-") || ft_strequ(op, "p++") || \
	ft_strequ(op, "p--"))
		return (UNPR);
	if (ft_strequ(op, "*") || ft_strequ(op, "/") || ft_strequ(op, "%"))
		return (MDM);
	if (ft_strequ(op, "+") || ft_strequ(op, "-"))
		return (AS);
	if (ft_strequ(op, "<") || ft_strequ(op, ">") || \
	ft_strequ(op, "<=") || ft_strequ(op, ">="))
		return (RO);
	if (ft_strequ(op, "==") || ft_strequ(op, "!="))
		return (EO);
	if (ft_strequ(op, "&&"))
		return (LA);
	if (ft_strequ(op, "||"))
		return (LO);
	return (INVALID);
}

static int	ft_prcd_enum(char *left, char *right)
{
	t_pr	l;
	t_pr	r;

	if (ft_strequ(left, "(") || ft_strequ(right, "("))
		return (0);
	if (ft_strequ(right, ")"))
		return (1);
	l = ft_pr_assign(left);
	r = ft_pr_assign(right);
	if (l == UNPR)
		return (r > l);
	else
		return (r >= l);
}

static void	ft_op_to_postfix(t_st *infix, t_st **stack, t_st **postfix)
{
	while (*stack && ft_prcd_enum((*stack)->op, infix->op))
	{
		ft_push_lst(postfix, (*stack)->op, (*stack)->type);
		ft_pop_stack(stack);
	}
	if (ft_strequ(infix->op, ")"))
		ft_pop_stack(stack);
	else
		ft_push_stack(stack, infix->op, infix->type);
}

void		ft_itop_lst(t_st *infix, t_st **postfix)
{
	t_st	*stack;

	stack = NULL;
	while (infix)
	{
		if (!ft_operator_str(infix->op) && !ft_strequ(infix->type, "space"))
			ft_push_lst(postfix, infix->op, infix->type);
		else if (!ft_strequ(infix->type, "space"))
		{
			if (!stack)
				ft_push_stack(&stack, infix->op, infix->type);
			else
				ft_op_to_postfix(infix, &stack, postfix);
		}
		infix = infix->next;
	}
	while (stack)
	{
		ft_push_lst(postfix, stack->op, stack->type);
		ft_pop_stack(&stack);
	}
}
