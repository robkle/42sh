/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history_exp.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthan <dthan@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/19 14:52:30 by ihwang            #+#    #+#             */
/*   Updated: 2021/01/06 19:08:02 by dthan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static int		ft_construct_exp(char **line, char *exp, char **split, char **exp_split)
{
	char	*tmp;
	int		r;	
	
	if (exp)
	{
		r = 1;
		tmp = ft_strjoin(exp, exp_split[1]);
		*line = ft_strjoin(split[0], tmp);
		free(tmp);
	}
	else
	{
		r = 0;
		*line = ft_strnew(0);
		ft_printf("%s: %s: event not found\n", SHELL_NAME, exp_split[0]);
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

	i = g_shell.history->curr;
	while (--i >= 0)
	{
		if (ft_strnequ(str, g_shell.history->hist[i], ft_strlen(str)))
			return (i);
	}
	return (-1);
}

static int		ft_expand_exp(char **line, char **split, char **exp_split)
{
	char	*exp;
	int		num;
	
	if (exp_split[0][1] == '!')
		exp = g_shell.history->curr - 1 >= 0 ? ft_strdup(g_shell.history->hist[g_shell.history->curr - 1]) : NULL;
	else if (ft_isdigit(exp_split[0][1]))
	{
		num = ft_atoi(&exp_split[0][1]);
		exp = num <= g_shell.history->curr && num > 0 ? ft_strdup(g_shell.history->hist[num - 1]) : NULL;
	}
	else if (exp_split[0][1] == '-')
	{
		num = ft_atoi(&exp_split[0][2]);
		exp = g_shell.history->curr - num >= 0 && num > 0 ? ft_strdup(g_shell.history->hist[g_shell.history->curr - num]) : NULL;
	}
	else
	{
		num = ft_str_search(&exp_split[0][1]);
		exp = num >= 0 ? ft_strdup(g_shell.history->hist[num]) : NULL;
	}
	free(*line); 
	return (ft_construct_exp(line, exp, split, exp_split));
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
		while (str[i] && !ft_isspace(str[i])) // be carefull with this since it is for word
			i++;
		exp_split[0] = ft_strsub(str, 0, i);
		exp_split[1] = ft_strdup(&str[i]);
	}
}

static void	ft_hist_exp_quote(char c, int *q, t_prompt pr)
{
	if (pr == PROMPT_QUOTE)
		*q = 1;
	else if (pr == PROMPT_QUOTE)
		*q = 2;
	else if (c == 39 && *q != 2)
		*q = !*q ? 1 : 0;
	else if (c == 34 && *q != 1)
		*q = !*q ? 2 : 0;
}		

int		ft_hist_exp(char **line, t_prompt pr)
{
	char *str;
	int		i;
	int		q;
	char	*split[2];
	char	*exp_split[2];

	q = 0;
	i = -1;
	str = *line;
	while (str[++i])
	{
		ft_hist_exp_quote(str[i], &q, pr);
		if (!(q % 2) && str[i] == '!' && str[i + 1] && str[i + 1] != '=' && \
			str[i + 1] != '(' && !ft_isspace(str[i + 1]))
		{
			split[0] = ft_strsub(str, 0, i);
			split[1] = ft_strdup(&str[i]);
			ft_split_exp(exp_split, split[1]);
			if (!ft_expand_exp(line, split, exp_split))
				return (0);
			ft_hist_exp(line, pr);
			return (1);
		}
	}
	return (0);
}
