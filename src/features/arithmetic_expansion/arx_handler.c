/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arx_handler.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rklein <rklein@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/01 14:19:47 by rklein            #+#    #+#             */
/*   Updated: 2021/04/01 15:19:41 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int			ft_arx_assign(t_process *p)
{
	t_assignment	*ptr;

	ptr = p->first_assignment;
	while (ptr)
	{
		if (ft_is_arithmetic_expansion(ptr->data))
		{
			if (ft_arx_replace_redi(&ptr->data) == EXIT_FAILURE)
				return (EXIT_FAILURE);
		}
		ptr = ptr->next;
	}
	return (EXIT_SUCCESS);
}

int			ft_arx_redi(t_process *p)
{
	t_redi	*redi_ptr;

	redi_ptr = p->first_redi;
	while (redi_ptr)
	{
		if (ft_is_arithmetic_expansion(redi_ptr->word))
		{
			if (ft_arx_replace_redi(&redi_ptr->word) == EXIT_FAILURE)
				return (EXIT_FAILURE);
		}
		redi_ptr = redi_ptr->next;
	}
	return (EXIT_SUCCESS);
}

/*
** Loops through av, checks each for arx.
** If arx is found it is send to be expanded
*/

int			ft_arx_av(t_process *p)
{
	int		i;

	i = -1;
	while (p->av[++i])
	{
		if (ft_is_arithmetic_expansion(p->av[i]))
		{
			if (ft_arx_replace_av(p->av, i) == EXIT_FAILURE)
				return (EXIT_FAILURE);
		}
	}
	return (EXIT_SUCCESS);
}

int			ft_arx(t_process *p)
{
	if (ft_arx_redi(p) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (ft_arx_av(p) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (ft_arx_assign(p) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
