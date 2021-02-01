/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intvar.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rklein <rklein@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/01 10:48:47 by rklein            #+#    #+#             */
/*   Updated: 2021/02/01 12:28:54 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static void	ft_update_value(t_var *intern_var, char *op)
{
	char	*tmp;
	int		val;

	val = ft_atoi(intern_var->value);
	tmp = intern_var->value;
	if (ft_strequ(op, "p++") || ft_strequ(op, "s++"))
		intern_var->value = ft_itoa(val + 1);
	if (ft_strequ(op, "p--") || ft_strequ(op, "s--"))
		intern_var->value = ft_itoa(val - 1);
	if (tmp)
		free(tmp);
}

void		ft_intvar(t_st *stack, char *op)
{
	t_var	*tmp_var;
	t_var	*intern_var;
	int		is_var;

	intern_var = (t_var*)ft_memalloc(sizeof(t_var));
	tmp_var = ft_getvar(stack->op);
	is_var = tmp_var ? 1 : 0;
	intern_var->name = is_var ? ft_strdup(tmp_var->name) : ft_strdup(stack->op);
	intern_var->value = is_var ? ft_strdup(tmp_var->value) : ft_strdup("0");
	intern_var->exported = is_var ? tmp_var->exported : 0;
	if (ft_strequ(op, "p++") || ft_strequ(op, "p--"))
		ft_update_value(intern_var, op);
	ft_modify_link(stack, intern_var->value, "integer");
	if (ft_strequ(op, "s++") || ft_strequ(op, "s--"))
		ft_update_value(intern_var, op);
	if (is_var)
		update_intern_var(intern_var);
	else
		add_intern_var(intern_var);
}
