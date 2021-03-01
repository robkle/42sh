/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parameter_expansion.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthan <dthan@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/08 03:24:07 by dthan             #+#    #+#             */
/*   Updated: 2021/02/27 20:25:02 by dthan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int	parameter_expansion_replace_av(char **av, int i)
{
	t_parameter_expansion	*ex;
	char					*temp;

	temp = av[i];
	if ((ex = constructor_parameter_expansion_struct(av[i])) == NULL)
		return (EXIT_FAILURE);
	av[i] = parameter_expansion_tool_replace(temp, ex->needle, ex->replacement);
	(temp) ? free(temp) : 0;
	destructor_parameter_expansion_struct(ex);
	if (is_parameter_expansion(av[i]))
		return (parameter_expansion_replace_av(av, i));
	return (EXIT_SUCCESS);
}

/*
** comment: need to reorder av?
*/

int	parameter_expansion_in_av(t_process *p)
{
	int i;

	i = -1;
	while (p->av[++i])
	{
		if (is_parameter_expansion(p->av[i]))
			if (parameter_expansion_replace_av(p->av, i) == EXIT_FAILURE)
				return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

int	parameter_expansion_replace_redi(char **word)
{
	t_parameter_expansion	*ex;
	char					*temp;

	temp = *word;
	if ((ex = constructor_parameter_expansion_struct(*word)) == NULL)
		return (EXIT_FAILURE);
	*word = parameter_expansion_tool_replace(temp, ex->needle, ex->replacement);
	(temp) ? free(temp) : 0;
	destructor_parameter_expansion_struct(ex);
	if (is_parameter_expansion(*word))
		return (parameter_expansion_replace_redi(word));
	return (EXIT_SUCCESS);
}

int	parameter_expansion_in_redi(t_process *p)
{
	t_redi *redi_ptr;

	redi_ptr = p->first_redi;
	while (redi_ptr)
	{
		if (is_parameter_expansion(redi_ptr->word))
			if (parameter_expansion_replace_redi(&redi_ptr->word) ==
				EXIT_FAILURE)
				return (EXIT_FAILURE);
		redi_ptr = redi_ptr->next;
	}
	return (EXIT_SUCCESS);
}

int parameter_expansion_in_assignment(t_process *p)
{
	t_assignment *ptr;

	ptr = p->first_assignment;
	while (ptr)
	{
		if (is_parameter_expansion(ptr->data))
			if (parameter_expansion_replace_redi(&ptr->data) ==
				EXIT_FAILURE)
				return (EXIT_FAILURE);
		ptr = ptr->next;
	}
	return (EXIT_SUCCESS);
}
