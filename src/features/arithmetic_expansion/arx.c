#include "shell.h"

void	ft_free_lst(t_st **lst)
{
	t_st *tmp;
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

static void	ft_arx_replace(char **av, int i, long long res)
{
	char	*tmp;

	tmp = av[i];
	av[i] = ft_llitoa(res);
	free(tmp);
}

static int	ft_is_arx(char *str)
{
	int	len;

	len = ft_strlen(str);
	return (ft_strnequ(str, "$((", 3) && str[len - 2] == ')' && \
	str[len - 1] == ')');
}

int	ft_arx(t_process *p)
{
	t_st				*infix;
	t_st				*postfix;
	char				*exp;
	long long int		res;
	int					i;
	
	i = -1;
	while (p->av[++i])
	{
		if (ft_is_arx(p->av[i]))
		{
			//think about clustered expansions $(($((exp1))+$((exp2))))
			exp = p->av[i];
			infix = NULL;
			postfix = NULL;
			if (!(infix = ft_extolst(&exp[1])))
				return (EXIT_FAILURE);
			ft_itop_lst(infix, &postfix);
			res = ft_calc(postfix);
			ft_arx_replace(p->av, i, res);
			ft_free_lst(&infix);
			ft_free_lst(&postfix);
		}
	}
	return (EXIT_SUCCESS);
}
