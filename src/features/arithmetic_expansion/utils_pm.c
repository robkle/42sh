/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_pm.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/01 19:33:11 by marvin            #+#    #+#             */
/*   Updated: 2021/02/01 19:47:48 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

t_st	*ft_skip_space(t_st *link, const int move)
{
	while (link && ft_strequ(link->type, "space"))
		link = move ? link->next : link->prev;
	return (link);
}

int		ft_isunary(t_st *infix)
{
	t_st *tmp;

	tmp = ft_skip_space(infix->prev, 0);
	if (!tmp)
		return (1);
	if (ft_strequ(tmp->type, "operator") && !ft_strequ(tmp->op, "s++") && \
	!ft_strequ(tmp->op, "s--"))
		return (1);
	return (0);
}

int		ft_issuf(t_st *infix)
{
	t_st	*tmp1;
	t_st	*tmp2;

	tmp1 = ft_skip_space(infix->prev, 0);
	if (ft_strlen(infix->op) >= 2)
	{
		if ((ft_strnequ(infix->op, "++", 2) || \
		ft_strnequ(infix->op, "--", 2)) && tmp1)
		{
			if (ft_strequ(tmp1->type, "intvar"))
			{
				tmp2 = ft_skip_space(tmp1->prev, 0);
				if (!tmp2 || (!ft_strequ(tmp2->op, "p++") && \
				!ft_strequ(tmp2->op, "p--")))
					return (1);
			}
		}
	}
	return (0);
}

int		ft_ispre(t_st *infix)
{
	int		i;
	t_st	*tmp;

	i = ft_strlen(infix->op);
	tmp = ft_skip_space(infix->next, 1);
	if (i >= 2)
	{
		if ((ft_strequ(&infix->op[i - 2], "++") || \
		ft_strequ(&infix->op[i - 2], "--")) && tmp)
		{
			if (ft_strequ(tmp->type, "intvar"))
				return (1);
		}
	}
	return (0);
}

int		ft_pref_suf_check(t_st *infix, t_st *begin)
{
	t_st	*tmp;

	tmp = ft_skip_space(infix->prev, 0);
	if (infix->op[0] == 'p' && tmp)
	{
		if (!ft_strequ(tmp->type, "operator"))
		{
			ft_print_error(SNERR, infix, begin);
			return (0);
		}
	}
	return (1);
}
