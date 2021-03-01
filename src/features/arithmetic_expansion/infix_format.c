/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   infix_format.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rklein <rklein@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/25 12:25:19 by rklein            #+#    #+#             */
/*   Updated: 2021/03/01 11:04:09 by rklein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static void	ft_link_merging(t_st *infix)
{
	t_st	*tmp;
	char	*merge;
	char	*tstr;

	merge = ft_strjoin(infix->op, infix->next->op);
	tstr = infix->op;
	infix->op = merge;
	free(tstr);
	tmp = infix->next;
	infix->next = infix->next->next;
	if (infix->next->next)
		infix->next->prev = infix;
	ft_free_link(tmp);
}

static void	ft_link_merge(t_st **infix)
{
	t_st	*begin;

	begin = *infix;
	while (*infix && (*infix)->next)
	{
		if ((ft_strequ((*infix)->type, "operand") || \
		ft_strequ((*infix)->type, "plusminus")) && \
		ft_strequ((*infix)->type, (*infix)->next->type))
		{
			ft_link_merging(*infix);
			*infix = begin;
		}
		else
			*infix = (*infix)->next;
	}
	*infix = begin;
}

static void	ft_quote_strip(t_st **infix)
{
	t_st	*begin;
	t_st	*tmp;

	begin = *infix;
	while (*infix)
	{
		if (ft_strequ((*infix)->type, "space") && ft_strequ((*infix)->op, "\""))
		{
			tmp = *infix;
			if ((*infix)->prev == NULL)
			{
				begin = (*infix)->next;
				begin->prev = NULL;
			}
			else
				ft_arx_skip_link(*infix);
			ft_free_link(tmp);
			*infix = begin;
		}
		else
			*infix = (*infix)->next;
	}
	*infix = begin;
}

void		ft_infix_format(t_st **infix)
{
	t_st	*begin;

	begin = *infix;
	ft_quote_strip(&begin);
	ft_link_merge(&begin);
}
