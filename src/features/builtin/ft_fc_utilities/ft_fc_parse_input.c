/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fc_parse_input.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthan <dthan@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/13 13:50:03 by dthan             #+#    #+#             */
/*   Updated: 2021/03/13 20:33:11 by dthan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int fc_is_option(char c)
{
	if (c == 'l' || c == 'n' || c == 'r' || c == 's' || c == 'e')
		return (1);
	return (0);
}

int fc_get_option(char c)
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

int fc_print_usage(void)
{
	ft_dprintf(2, "fc: usage: fc [-e ename] [-lnr] ");
	ft_dprintf(2, "[first] [last] or fc -s [pat=rep] [command]\n");
	return (EXIT_FAILURE);
}

int fc_error_invalid_option(char op)
{
	ft_dprintf(2, "%s: fc: -%c: invalid option\n", SHELL_NAME, op);
	return (fc_print_usage());
}

int fc_error_option_requires_an_argument(void)
{
	ft_dprintf(2, "%s: fc: -e: option requires an argument\n", SHELL_NAME);
	return (fc_print_usage());
}

// int		fc_get_options(char *str, char *str_next, int *ops, char **editor)
// {
// 	int i;
// 	int op;

// 	i = 0;
// 	while (str[++i])
// 	{
// 		op = fc_get_option(str[i]);
// 		if (op == 0)
// 			return (fc_error_invalid_option(str[i]));
// 		else if (op & FC_E_OP)
// 		{
// 			if (str_next || str[i + 1])
// 			{
// 				char *temp = *editor;
// 				*editor = (str[i + 1]) ? ft_strdup(&str[i + 1]) : ft_strdup(str_next);
// 				free(temp);
// 				*ops |= op;
// 				if (str[i + 1])
// 					return (EXIT_SUCCESS);
// 				return (2);
// 			}
// 			else
// 				return (fc_error_option_requires_an_argument());
// 		}
// 		else
// 			*ops |= op;
// 	}
// 	return (EXIT_SUCCESS);
// }


int fc_exchange_editor(t_ft_fc *self, int op, char *str_next, char *parsed_str)
{
	char *temp;

	temp = self->editor;
	self->editor = (parsed_str[0] != '\0') ? ft_strdup(parsed_str) : ft_strdup(str_next);
	free(temp);
	self->ops |= op;
	if (parsed_str[0])
		return (EXIT_SUCCESS);
	return (2);
}

int		fc_get_options(char *str, char *str_next, t_ft_fc *self)
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

// int fc_parse_input(t_process *p, int *ops, char **editor, char **block)
// {
// 	int i;
// 	int ret;

// 	i = 0;
// 	while (p->av[++i] && p->av[i][0] == '-' && p->av[i][1])
// 	{
// 		if (ft_num_check(p->av[i])) // need to check this later
// 			break;
// 		ret = fc_get_options(p->av[i], p->av[i + 1], ops, editor);
// 		if (ret == EXIT_FAILURE)
// 			return (EXIT_FAILURE);
// 		else if (ret == 2)
// 			i++;
// 	}
// 	(i < p->ac && p->av[i] && ft_strchr(p->av[i], '=')) ? block[REPLACE] = ft_strdup(p->av[i++]) : 0;
// 	(i < p->ac && p->av[i]) ? block[FIRST] = ft_strdup(p->av[i++]) : 0;
// 	(i < p->ac && p->av[i]) ? block[LAST] = ft_strdup(p->av[i]) : 0;
// 	return (EXIT_SUCCESS);
// }

int fc_parse_input(t_process *p, t_ft_fc *self)
{
	int i;
	int ret;

	i = 0;
	while (p->av[++i] && p->av[i][0] == '-' && p->av[i][1])
	{
		if (ft_num_check(p->av[i]))
			break;
		ret = fc_get_options(p->av[i], p->av[i + 1], self);
		if (ret == EXIT_FAILURE)
			return (EXIT_FAILURE);
		else if (ret == 2)
			i++;
	}
	(i < p->ac && p->av[i] && ft_strchr(p->av[i], '=')) ? self->blocks[REPLACE] = ft_strdup(p->av[i++]) : 0;
	(i < p->ac && p->av[i]) ? self->blocks[FIRST] = ft_strdup(p->av[i++]) : 0;
	(i < p->ac && p->av[i]) ? self->blocks[LAST] = ft_strdup(p->av[i]) : 0;
	return (EXIT_SUCCESS);
}
