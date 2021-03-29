/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arx_check.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rklein <rklein@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/29 11:02:52 by rklein            #+#    #+#             */
/*   Updated: 2021/03/29 17:43:15 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

/*
** Checks if av[i] contains arx
*/

int		ft_is_arithmetic_expansion(char *str)
{
	int	i;
	int	sq;

	sq = 0;
	i = -1;
	while (str[++i])
	{
		if (str[i] == '\'' && is_real_character(str, i))
			sq = sq ? 0 : 1;
		if (str[i] == '$' && is_real_character(str, i) && str[i + 1] && \
			str[i + 1] == '(' && str[i + 2] && str[i + 2] == '(' && !sq)
			return (1);
	}
	return (0);
}

/*
** Finds range of arx expansion
*/

int		ft_arx_get_range(char *str, int range[])
{
	int i;

	i = -1;
	while (str[++i])
	{
		if (str[i] == '$' && is_real_character(str, i) && str[i + 1] && \
			str[i + 1] == '(' && str[i + 2] && str[i + 2] == '(')
		{
			range[0] = i;
			if(ft_jump_arx_exp(str, &i) == EXIT_FAILURE)
				return (EXIT_FAILURE);
			range[1] = i;
			break ;
		}
	}
	return (EXIT_SUCCESS);	
}

/*
** find end of arx
*/

int		ft_jump_arx_exp(char *str, int *i)
{
	int	stack;

	stack = 0;
	while (str[++(*i)])
	{
		if (str[*i] == '(')
			stack++;
		else if (str[*i] == ')')
			stack--;
		else if ((str[*i] == '"' || str[*i] == '\'' || str[*i] == '\\') &&
				is_real_character(str, *i))
		{
			if (jump_quote(str, i, str[*i]) == EXIT_FAILURE)
				return (EXIT_FAILURE);
		}
		if (stack == 0)
			break ;
	}
	if (str[*i] == '\0' || !ft_strnequ(&str[*i - 1], "))", 2))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
