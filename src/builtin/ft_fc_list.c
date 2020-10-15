#include "shell.h"

static void	ft_fc_print(int *r_ind, int flags)
{
	int i;		

	i = r_ind[0];
	if (i <= r_ind[1])
	{
		while (i <= r_ind[1])
		{
			if ((flags & 1) && !(flags & 2))
				ft_printf("%d", i + 1);
			ft_printf("\t%s\n", g_h->hist[i]);
			i++;
		}
	}
	else
	{
		while (i >= r_ind[1])
		{
			if ((flags & 1) && !(flags & 2))
				ft_printf("%d", i + 1);
		
			ft_printf("\t%s\n", g_h->hist[i]);
			i--;
		}
	}
}

int	ft_fc_range(char *str)
{
	int	i;
	int index;

	i = -1;
	while (str[++i])
	{
		if (!ft_isdigit(str[i]))
		{
			index = g_h->curr - 1;
			while (--index >= 0)
			{
				if (ft_strequ(g_h->hist[index], str))
					return (index);
			}
			return (-1);
		}
	}
	index = ft_atoi(str);
	return (index < 0 ? (g_h->curr - 1) - index : index - 1);
}

static void		ft_swap(int *nums)
{
	int	tmp;
	
	tmp = nums[0];
	nums[0] = nums[1];
	nums[1] = tmp;
}

int	ft_fc_list(int flags, char **range)
{
	int	r_ind[2];
	int	min;
	
	if (!range[0])
	{
		min = (g_h->curr - 1) - HISTSIZE ? (g_h->curr - 1) - HISTSIZE : 0;
		r_ind[0] = flags & 4 ? g_h->curr - 2 : min;
		r_ind[1] = flags & 4 ? min : g_h->curr - 2;
	}
	else
		r_ind[0] = ft_fc_range(range[0]);
	if (range[1])
		r_ind[1] = ft_fc_range(range[1]);
	if (r_ind[0] < 0 || r_ind[1] < 0)
	{
		ft_printf("bash: fc: history specification out of range\n");
		return (0);
	}
	if ((flags & 4) && r_ind[0] < r_ind[1])
		ft_swap(r_ind);
	ft_fc_print(r_ind, flags);
	return (1);
}
