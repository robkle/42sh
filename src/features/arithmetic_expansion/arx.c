/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arx.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rklein <rklein@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/26 20:28:05 by rklein            #+#    #+#             */
/*   Updated: 2021/03/29 20:16:06 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int			ft_arx_lexer(char *arx, long long int *res)
{
	char	**arx_token;
	char	*exp;
	char	*tmp;
	int		i;

	arx_token = ft_expsplit(arx);
	i = -1;
	while (arx_token[++i])
	{
		if (!(ft_bracket_check(arx_token[i], 1)))
		{
			exp = ft_strjoin(arx_token[i], arx_token[i + 1]);
			tmp = arx_token[i];
			arx_token[i] = exp;
			free(tmp);
			ft_arx_token_move(arx_token, i);
			i = -1;
		}
	}
	return (ft_arx_token_exp(arx_token, res));
}

/*
**replace the expansion in av[i] with res
*/

static void	ft_arx_replace_with_res(char **str, char *split[],
long long int res)
{
	char *tmp1;
	char *tmp2;
	char *replace;

	replace = ft_llitoa(res);
	tmp1 = ft_strjoin(split[0], replace);
	tmp2 = ft_strjoin(tmp1, split[2]);
	free(replace);
	free(split[0]);
	free(split[1]);
	free(split[2]);
	free(tmp1);
	tmp1 = *str;
	*str = tmp2;
	free(tmp1);
}

/*
** Function that gets range, sends range for expansion,
** and replace range with res
*/

static int	ft_arx_expand(char **str)
{
	long long int	res;
	int				range[2];
	char			*split[3];

	range[0] = 0;
	range[1] = 0;
	if (ft_arx_get_range(*str, range) == EXIT_FAILURE)
	{
		ft_dprintf(2, "42sh: syntax error in expression\n");
		return (EXIT_FAILURE);
	}
	split[0] = ft_strndup(*str, range[0]);
	split[1] = ft_strsub(*str, range[0], (range[1] - range[0]) + 1);
	split[2] = ft_strdup(&(*str)[range[1] + 1]);
	if (!(ft_arx_lexer(ft_strdup(split[1]), &res)))
	{
		free(split[0]);
		free(split[1]);
		free(split[2]);
		return (EXIT_FAILURE);
	}
	ft_arx_replace_with_res(str, split, res);
	return (EXIT_SUCCESS);
}

/*
** recursive function that sends each arx in av[i] for expansion
*/

static int	ft_arx_replace_av(char **av, int i)
{
	char *arx;
	char *tmp;

	arx = ft_strdup(av[i]);
	if (ft_arx_expand(&arx) == EXIT_FAILURE)
	{
		free(arx);
		return (EXIT_FAILURE);
	}
	tmp = av[i];
	av[i] = arx;
	free(tmp);
	if (ft_is_arithmetic_expansion(av[i]))
		return (ft_arx_replace_av(av, i));
	return (EXIT_SUCCESS);
}

/*
** Loops through av, checks each for arx.
** If arx is found it is send to be expanded
*/

int			ft_arx(t_process *p)
{
	int		i;

	i = -1;
	while (p->av[++i])
	{
		if (ft_is_arithmetic_expansion(p->av[i]))
		{
			if (ft_arx_replace_av(p->av, i) == EXIT_FAILURE)
				return (EXIT_FAILURE);
		}
	}
	return (EXIT_SUCCESS);
}
