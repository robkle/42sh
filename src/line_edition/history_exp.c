/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   carriage_return.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tango <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/02 15:29:56 by tango             #+#    #+#             */
/*   Updated: 2020/08/05 05:42:43 by tango            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static int		ft_construct_exp(t_l *l, char *exp, char **split, char **exp_split)
{
	char	*tmp;
	int		r;	
	
	if (exp)
	{
		r = 1;
		tmp = ft_strjoin(exp, exp_split[1]);
		l->line = ft_strjoin(split[0], tmp);
		free(tmp);
	}
	else
	{
		r = 0;
		l->line = ft_strnew(0);
		ft_printf("\n42sh: %s: event not found", exp_split[0]);
	}
	free(exp);
	free(split[0]);
	free(split[1]);
	free(exp_split[0]);
	free(exp_split[1]);
	return (r);
}

static int		ft_str_search(char *str)
{
	int	i;

	i = g_h->curr;
	while (--i >= 0)
	{
		if (ft_strnequ(str, g_h->hist[i], ft_strlen(str)))
			return (i);
	}
	return (-1);
}
	
static int		ft_expand_exp(t_l *l, char **split, char **exp_split)
{
	char	*exp;
	int		num;
	
	if (exp_split[0][1] == '!')
		exp = g_h->curr - 1 >= 0 ? ft_strdup(g_h->hist[g_h->curr - 1]) : NULL;
	else if (ft_isdigit(exp_split[0][1]))
	{
		num = ft_atoi(&exp_split[0][1]);
		exp = num <= g_h->curr && num > 0 ? ft_strdup(g_h->hist[num - 1]) : NULL;
	}
	else if (exp_split[0][1] == '-')
	{
		num = ft_atoi(&exp_split[0][2]);
		exp = g_h->curr - num >= 0 && num > 0 ? ft_strdup(g_h->hist[g_h->curr - num]) : NULL;
	}
	else
	{
		num = ft_str_search(&exp_split[0][1]);
		exp = num >= 0 ? ft_strdup(g_h->hist[num]) : NULL;
	}
	free(l->line); 
	return (ft_construct_exp(l, exp, split, exp_split));
}

static void		ft_split_exp(char **exp_split, char *str)
{
	int		i;

	if (str[1] == '!')
	{
		exp_split[0] = ft_strsub(str, 0, 2);
		exp_split[1] = ft_strdup(&str[2]);
	}
	else if (str[1] == '-' || ft_isdigit(str[1]))
	{
		i = 2;
		while(ft_isdigit(str[i]))
			i++;
		exp_split[0] = ft_strsub(str, 0, i);
		exp_split[1] = ft_strdup(&str[i]);
	}
	else
	{
		i = 1;
		while (str[i] && !ft_isspace(str[i]))
			i++;
		exp_split[0] = ft_strsub(str, 0, i);
		exp_split[1] = ft_strdup(&str[i]);
	}
}

int		ft_hist_exp(t_l *l)
{
	int		i;
	char	*split[2];
	char	*exp_split[2];

	i = -1;
	while (l->line[++i])
	{
		if (l->line[i] == '!' && l->line[i + 1] && !ft_isspace(l->line[i + 1])
				&& l->line[i + 1] != '=' && l->line[i + 1] != '(')
		{
			split[0] = ft_strsub(l->line, 0, i);
			split[1] = ft_strdup(&l->line[i]);
			ft_split_exp(exp_split, split[1]);
			if (!ft_expand_exp(l, split, exp_split))
				return (0);
			ft_hist_exp(l);
			return (1);
		}
	}
	return (0);
}
