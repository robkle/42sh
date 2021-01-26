/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parameter_expansion.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthan <dthan@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/08 03:24:07 by dthan             #+#    #+#             */
/*   Updated: 2021/01/26 07:49:37 by dthan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

/*
int parameter_expansion_replace_redi(t_redi *redi)
{
	char *temp;
	char *replacement;

	temp = redi->word;
	// find the replacement
	replacement = ft_itoa(g_shell.exit_status);
	redi->word = replace_replace(temp, "${?}", replacement);
	free(replacement);
	free(temp);
	if (is_parameter_expansion(redi->word))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int parameter_expansion_in_redi(t_process *p)
{
	t_redi *redi_ptr;

	redi_ptr = p->first_redi;
	while (redi_ptr)
	{
		if (is_parameter_expansion(redi_ptr->word))
			if (parameter_expansion_replace_redi(redi_ptr) == EXIT_FAILURE)
				return (EXIT_FAILURE);
		redi_ptr = redi_ptr->next;
	}
	return (EXIT_SUCCESS);
}
*/

int parameter_expansion_replace_av(char **av, int i)
{
	t_parameter_expansion *ex;
	char *temp;

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

// reordering av?
int parameter_expansion_in_av(t_process *p)
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
