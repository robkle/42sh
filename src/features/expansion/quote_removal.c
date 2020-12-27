/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_removal.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthan <dthan@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/17 13:52:13 by dthan             #+#    #+#             */
/*   Updated: 2020/12/25 18:12:06 by dthan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static char *remove_quote(char *str)
{
	int i;
	char *new;

	if (!str)
		return (NULL);
	i = -1;
	new = ft_strnew(0);
	while (str[++i])
	{
		if (str[i] == '\\' || str[i] == '\'' ||  str[i] == '"')
			continue;
		new = ft_strbuilder_char(new, str[i]);
	}
	free(str);
	return (new);
}

static int is_quoted(char *str)
{
	int i;

	i = -1;
	while (str[++i])
		if (str[i] == '\\' || str[i] == '\'' ||  str[i] == '"')
			return (1);
	return (0);
}

static void quote_removal_in_av(t_process *p)
{
	int i;

	i = -1;
	while (p->av[++i] && i < MAX_ARGV)
	{
		if (is_quoted(p->av[i]))
			p->av[i] = remove_quote(p->av[i]);
	}
}

static void quote_removal_in_redi(t_process *p)
{
	t_redi *redi_ptr;

	redi_ptr = p->first_redi;
	while (redi_ptr)
	{
		if (!ft_strequ(redi_ptr->op, "<<") && is_quoted(redi_ptr->word))
			redi_ptr->word = remove_quote(redi_ptr->word);
		redi_ptr = redi_ptr->next;
	}
}

int quote_removal(t_process *p)
{
	quote_removal_in_av(p);
	quote_removal_in_redi(p);
	return (EXIT_SUCCESS);
}