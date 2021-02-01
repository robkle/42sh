/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_exp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rklein <rklein@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/01 10:55:14 by rklein            #+#    #+#             */
/*   Updated: 2021/02/01 12:02:39 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int		ft_expansion_len(char *exp)
{
	int	i;

	if (ft_strnequ(exp, "$((", 3))
		return (ft_arx_brackets(exp));
	else if (ft_isalpha(exp[1]) || exp[1] == '_')
	{
		i = 2;
		while (ft_isalnum(exp[i]) || exp[i] == '_')
			i++;
		return (i);
	}
	return (0);
}

char	**ft_split_arx(char *arx, int index, int len)
{
	char	**exp;

	exp = (char **)malloc(sizeof(char *) * 4);
	exp[0] = ft_strsub(arx, 0, index);
	exp[1] = ft_strsub(arx, index, len);
	exp[2] = ft_strdup(&arx[index + len]);
	exp[3] = NULL;
	return (exp);
}

char	*ft_strcombine(char **exp, char *res)
{
	int		len;
	char	*arx;

	len = ft_strlen(exp[0]);
	len += ft_strlen(res);
	len += ft_strlen(exp[2]);
	arx = (char *)ft_memalloc(sizeof(char) * len + 1);
	ft_strcpy(arx, exp[0]);
	ft_strcat(arx, res);
	ft_strcat(arx, exp[2]);
	free(res);
	ft_arraydel(exp);
	return (arx);
}

int		ft_arx_brackets(char *exp)
{
	char	stack[1024];
	int		i;
	int		j;

	i = 2;
	j = 0;
	ft_bzero(stack, 1024);
	while (exp[++i])
	{
		if (exp[i] == '(')
			stack[j++] = '(';
		else if (exp[i] == ')' && exp[i + 1] == ')' && !stack[0])
			return (i + 2);
		else if (exp[i] == ')')
		{
			if (j > 0 && stack[j - 1] == '(')
				stack[--j] = '\0';
			else
				return (0);
		}
	}
	return (0);
}

void	ft_free_lst(t_st **lst)
{
	t_st	*tmp;

	while (*lst)
	{
		tmp = (*lst)->next;
		free((*lst)->op);
		free((*lst)->type);
		free(*lst);
		*lst = tmp;
	}
	*lst = NULL;
}
