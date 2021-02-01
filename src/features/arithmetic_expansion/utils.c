/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rklein <rklein@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/01 10:55:05 by rklein            #+#    #+#             */
/*   Updated: 2021/02/01 11:39:02 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	ft_modify_link(t_st *infix, char *op, char *type)
{
	char	*tmp;

	if (op)
	{
		tmp = infix->op;
		infix->op = ft_strdup(op);
		free(tmp);
	}
	if (type)
	{
		tmp = infix->type;
		infix->type = ft_strdup(type);
		free(tmp);
	}
}

t_st	*ft_last_link(t_st *lst)
{
	t_st	*current;
	t_st	*next;

	current = lst;
	next = lst->next;
	while (next)
	{
		current = current->next;
		next = next->next;
	}
	return (current);
}

void	ft_push_lst(t_st **infix, char *op, char *type)
{
	t_st	*begin;

	if (*infix == NULL)
	{
		begin = malloc(sizeof(t_st));
		begin->op = ft_strdup(op);
		if (type)
			begin->type = ft_strdup(type);
		begin->prev = NULL;
		begin->next = NULL;
	}
	else
	{
		begin = *infix;
		*infix = ft_last_link(*infix);
		(*infix)->next = malloc(sizeof(t_st));
		(*infix)->next->prev = *infix;
		*infix = (*infix)->next;
		(*infix)->op = ft_strdup(op);
		if (type)
			(*infix)->type = ft_strdup(type);
		(*infix)->next = NULL;
	}
	*infix = begin;
}

void	ft_push_stack(t_st **stack, char *op, char *type)
{
	t_st	*tmp;

	if (*stack == NULL)
	{
		*stack = malloc(sizeof(t_st));
		(*stack)->op = ft_strdup(op);
		(*stack)->type = ft_strdup(type);
		(*stack)->next = NULL;
	}
	else
	{
		tmp = malloc(sizeof(t_st));
		tmp->op = ft_strdup(op);
		tmp->type = ft_strdup(type);
		tmp->next = *stack;
		*stack = tmp;
	}
}

void	ft_pop_stack(t_st **stack)
{
	t_st	*tmp;

	tmp = (*stack)->next;
	free((*stack)->op);
	free((*stack)->type);
	free(*stack);
	*stack = tmp;
}
