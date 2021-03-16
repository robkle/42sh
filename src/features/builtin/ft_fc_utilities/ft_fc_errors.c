/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fc_errors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthan <dthan@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/13 22:50:23 by dthan             #+#    #+#             */
/*   Updated: 2021/03/13 22:50:54 by dthan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static int	fc_print_usage(void)
{
	ft_dprintf(2, "fc: usage: fc [-e ename] [-lnr] ");
	ft_dprintf(2, "[first] [last] or fc -s [pat=rep] [command]\n");
	return (EXIT_FAILURE);
}

int			fc_error_invalid_option(char op)
{
	ft_dprintf(2, "%s: fc: -%c: invalid option\n", SHELL_NAME, op);
	return (fc_print_usage());
}

int			fc_error_option_requires_an_argument(void)
{
	ft_dprintf(2, "%s: fc: -e: option requires an argument\n", SHELL_NAME);
	return (fc_print_usage());
}

int			fc_error_history_specification_out_of_range(void)
{
	ft_dprintf(2, "%s: fc: history specification out of range\n", SHELL_NAME);
	return (EXIT_FAILURE);
}

int			fc_error_no_command_found(void)
{
	ft_dprintf(2, "%s: fc: no command found\n", SHELL_NAME);
	return (EXIT_FAILURE);
}
