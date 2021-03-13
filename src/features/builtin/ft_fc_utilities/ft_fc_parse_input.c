/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fc_parse_input.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthan <dthan@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/13 13:50:03 by dthan             #+#    #+#             */
/*   Updated: 2021/03/13 22:45:50 by dthan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static int	fc_is_option(char c)
{
	if (c == 'l' || c == 'n' || c == 'r' || c == 's' || c == 'e')
		return (1);
	return (0);
}

static int	fc_get_option(char c)
{
	if (fc_is_option(c))
	{
		if (c == 'l')
			return (FC_L_OP);
		else if (c == 'n')
			return (FC_N_OP);
		else if (c == 'r')
			return (FC_R_OP);
		else if (c == 's')
			return (FC_S_OP);
		else if (c == 'e')
			return (FC_E_OP);
	}
	return (0);
}

static int	fc_exchange_editor(
	t_ft_fc *self, int op, char *str_next, char *parsed_str)
{
	char *temp;

	temp = self->editor;
	self->editor = (parsed_str[0] != '\0') ?
		ft_strdup(parsed_str) : ft_strdup(str_next);
	free(temp);
	self->ops |= op;
	if (parsed_str[0])
		return (EXIT_SUCCESS);
	return (2);
}

static int	fc_get_options(char *str, char *str_next, t_ft_fc *self)
{
	int i;
	int op;

	i = 0;
	while (str[++i])
	{
		op = fc_get_option(str[i]);
		if (op == 0)
			return (fc_error_invalid_option(str[i]));
		else if (op & FC_E_OP)
		{
			if (str_next || str[i + 1])
				return (fc_exchange_editor(self, op, str_next, &str[i + 1]));
			else
				return (fc_error_option_requires_an_argument());
		}
		else
			self->ops |= op;
	}
	return (EXIT_SUCCESS);
}

int			fc_parse_input(t_process *p, t_ft_fc *self)
{
	int i;
	int ret;

	i = 0;
	while (p->av[++i] && p->av[i][0] == '-' && p->av[i][1])
	{
		if (ft_num_check(p->av[i]))
			break ;
		ret = fc_get_options(p->av[i], p->av[i + 1], self);
		if (ret == EXIT_FAILURE)
			return (EXIT_FAILURE);
		else if (ret == 2)
			i++;
	}
	(i < p->ac && p->av[i] && ft_strchr(p->av[i], '=')) ?
		self->blocks[REPLACE] = ft_strdup(p->av[i++]) : 0;
	(i < p->ac && p->av[i]) ? self->blocks[FIRST] = ft_strdup(p->av[i++]) : 0;
	(i < p->ac && p->av[i]) ? self->blocks[LAST] = ft_strdup(p->av[i]) : 0;
	return (EXIT_SUCCESS);
}
