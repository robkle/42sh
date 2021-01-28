#include "shell.h"

static int	ft_calc_exp(char *exp, long long int *res)
{
	t_st	*infix;
	t_st	*postfix;

	infix = NULL;
	postfix = NULL;
	if (!(infix = ft_extolst(&exp[1])))
		return (0);
	ft_itop_lst(infix, &postfix);
	*res = ft_calc(postfix);
	ft_free_lst(&infix);
	ft_free_lst(&postfix);
	return (1);
}

static int	ft_expand_arx(char *arx, long long int *res)
{
	int		i;
	char	**exp;
	int		len;

	i = ft_strlen(arx);
	while (--i >= 0)
	{
		if (arx[i] == '$')
		{
			if ((len = ft_expansion_len(&arx[i])))
			{
				exp = ft_split_arx(arx, i, len);
				if (!ft_calc_exp(exp[1], res))
				{
					ft_arraydel(exp);
					return (0);
				}
				free(arx);
				arx = ft_strcombine(exp, ft_llitoa(*res));
				i = ft_strlen(arx);
			}
		}
	}
	free(arx);
	return(1);
}

int	ft_arx(t_process *p)
{
	int					i;
	int					len;
	long long int		res;
	char				*tmp;
	
	i = -1;
	while (p->av[++i])
	{
		len = ft_strlen(p->av[i]);
		if (ft_strnequ(p->av[i], "$((", 3) && p->av[i][len - 2] == ')' && \
		p->av[i][len - 1] == ')')
		{
			if (!(ft_expand_arx(ft_strdup(p->av[i]), &res)))
				return (EXIT_FAILURE);
			tmp = p->av[i];
			p->av[i] = ft_llitoa(res);
			free(tmp);
		}
	}
	return (EXIT_SUCCESS);
}
