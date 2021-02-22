/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plusminus.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rklein <rklein@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/01 10:54:39 by rklein            #+#    #+#             */
/*   Updated: 2021/02/15 11:49:19 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static void	ft_pm_addnew(t_st *infix, char *op, char *type)
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
		free(str);
	}
	else
		ft_pm_split(infix, spec, size);
}

void		ft_plusminus(t_st **infix)
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
