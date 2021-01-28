#include "shell.h"

t_st	*ft_skip_space(t_st *link, const int move)
{
	while (link && ft_strequ(link->type, "space"))
		link = move ? link->next : link->prev;
	return (link);
}	

static int	ft_isunary(t_st *infix)
{
	t_st *tmp;

	tmp = ft_skip_space(infix->prev, 0);
	if (!tmp)
		return (1);
	if (ft_strequ(tmp->type, "operator") && !ft_strequ(tmp->op, "s++") && \
	!ft_strequ(tmp->op, "s--"))
		return (1);
	return (0);
}

static int	ft_issuf(t_st *infix)
{
	t_st	*tmp1;
	t_st	*tmp2;
	
	tmp1 = ft_skip_space(infix->prev, 0);
	if (ft_strlen(infix->op) >= 2)
	{
		if ((ft_strnequ(infix->op, "++", 2) || \
		ft_strnequ(infix->op, "--", 2)) && tmp1)
		{
			if (ft_strequ(tmp1->type, "intvar"))
			{
				tmp2 = ft_skip_space(tmp1->prev, 0);
				if (!tmp2 || (!ft_strequ(tmp2->op, "p++") && \
				!ft_strequ(tmp2->op, "p--")))
					return (1);
			}
		}
	}
	return (0);
}

static int	ft_ispre(t_st *infix)
{
	int		i;
	t_st	*tmp;

	i = ft_strlen(infix->op);
	tmp = ft_skip_space(infix->next, 1);
	if (i >= 2)
	{
		if ((ft_strequ(&infix->op[i - 2], "++") || \
		ft_strequ(&infix->op[i - 2], "--")) && tmp)
		{
			if (ft_strequ(tmp->type, "intvar"))
				return (1);
		}
	}
	return (0);
}

static void ft_pm_addnew(t_st *infix, char *op, char *type)
{
	t_st	*new;

	if (infix->next == NULL)
	{
		infix->next = malloc(sizeof(t_st));
		infix->next->prev = infix;
		new = infix->next;
		new->next = NULL;
	}
	else
	{
		new = malloc(sizeof(t_st));
		new->next = infix->next;
		new->prev = infix;
		infix->next->prev = new;
		infix->next = new;
	}
	new->op = NULL;
	new->type = NULL;
	ft_modify_link(new, op, type);
}

static void	ft_pm_split(t_st *infix, char *spec, int size)
{
	char	*split[2];
	
	if (ft_strequ(spec, "s"))
	{
		split[0] = ft_strjoin(spec, ft_strsub(infix->op, 0, 2));
		ft_pm_addnew(infix, &infix->op[2], "plusminus");
		ft_modify_link(infix, split[0], "operator");
	}
	else if (ft_strequ(spec, "p"))
	{
		split[0] = ft_strsub(infix->op, 0, size - 2);
		split[1] = ft_strjoin(spec, ft_strdup(&infix->op[size - 2]));
		ft_pm_addnew(infix, split[1], "operator");
		ft_modify_link(infix, split[0], "plusminus");
		free(split[1]);
	}
	else if (!spec[0] || ft_strequ(spec, "u"))
	{
		split[0] = spec ? ft_strjoin(spec, ft_strsub(infix->op, 0, 1)) : \
		ft_strsub(infix->op, 0, 1);
		ft_pm_addnew(infix, &infix->op[1], "plusminus");
		ft_modify_link(infix, split[0], "operator");
	}
	free(split[0]);
}

static void	ft_pm_create(t_st *infix, char *spec)
{
	char	*str;
	int		size;

	size = ft_strlen(infix->op);
	if ((size == 2 && (ft_strequ(spec, "s") || ft_strequ(spec, "p"))) || \
	size == 1)
	{
		str = ft_strjoin(spec, infix->op);
		ft_modify_link(infix, str, "operator");
	}

	else
		ft_pm_split(infix, spec, size);
}

void	ft_plusminus(t_st **infix)
{
	t_st	*begin;

	begin = *infix;
	while (*infix)
	{
		if (ft_strequ((*infix)->type, "plusminus"))
		{
			if (ft_issuf(*infix))
				ft_pm_create(*infix, "s");
			else if (ft_ispre(*infix))
				ft_pm_create(*infix, "p");
			else if (ft_isunary(*infix))
				ft_pm_create(*infix, "u");
			else
				ft_pm_create(*infix, "\0");
			*infix = begin;
		}
		else
			*infix = (*infix)->next;
	}
	*infix = begin;
}
