/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   atoi_base.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rklein <rklein@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/15 16:14:04 by rklein            #+#    #+#             */
/*   Updated: 2021/02/15 16:17:03 by rklein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static void ft_restolink(t_st *infix, long long int res)
{
	char	*tmp;
	tmp = ft_llitoa(res);
	ft_modify_link(infix, tmp, "integer");
	free(tmp);
}

int	ft_atoi_base(t_st *infix, char *value, int base, int calc)
{
	int				i;
	long long int	res;

	res = 0;
	if (value && *value)
	{
		while (*value)
		{
			i = -1;
			while (++i < base)
			{
				if (BVALS[i] == *value)
				{
					res = base * res + i;
					break ;
				}
			}
			if (i == base)
				return (0);
			value++;
		}
	}
	if (calc)
		ft_restolink(infix, res);
	return (1);
}