/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arx_exp.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rklein <rklein@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/01 10:43:04 by rklein            #+#    #+#             */
/*   Updated: 2021/03/01 10:40:04 by rklein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static int	ft_calc_exp(char *exp, long long int *res)
{
	t_st	*infix;
	t_st	*postfix;
	char	*calc;

	if (ft_bracket_check(exp, 0) == -1)
	{
		ft_printf("42sh: syntax error in expression\n");
		return (0);
	}
	infix = NULL;
	postfix = NULL;
	if (!(infix = ft_extolst(&exp[1])))
		return (0);
	ft_itop_lst(infix, &postfix);
	calc = ft_calc(postfix);
	ft_free_lst(&infix);
	ft_free_lst(&postfix);
	if (!calc)
		return (0);
	*res = ft_atolli(calc);
	free(calc);
	return (1);
}

static int	ft_expand_arx_whole(char *arx, long long int *res)
{
	if (!ft_calc_exp(arx, res))
	{
		free(arx);
		return (0);
	}
	free(arx);
	return (1);
}

int			ft_expand_arx(char *arx, long long int *res)
{
	int		i;
	char	**exp;
	int		len;

	i = ft_strlen(arx);
	while (--i >= 0)
	{
		if (arx[i] == '$')
		{
			if (i == 0 && (len = ft_arx_brackets(arx)))
				return (ft_expand_arx_whole(arx, res));
			else if ((len = ft_expansion_len(&arx[i])))
			{
				exp = ft_split_arx(arx, i, len);
				if (!ft_calc_exp(exp[1], res))
					return (ft_arx_free_exp(exp, arx));
				i = ft_update_arx(&arx, exp, *res);
			}
			else if (!len)
				return (ft_arx_free_exp_bracket(arx));
		}
	}
	free(arx);
	return (1);
}
