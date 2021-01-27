/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_removal.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthan <dthan@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/17 13:52:13 by dthan             #+#    #+#             */
/*   Updated: 2021/01/24 22:30:50 by dthan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

// 3 types of quoting
// backslah
// single quote
// double quote

/*
** algorithm for removing quote
** if it is backslash
** if it is dquote and quote
*/

char *remove_quoting(char *str, int *i)
{
	char quote;
	char buffer[4096];
	int j;

	ft_bzero(buffer, 4096);
	quote = str[*i];
	j = 0;
	while (str[++*i])
	{
		if (str[*i] == quote && is_real_character(str, *i))
			break ;
		buffer[j++] = str[*i];
	}
	return (ft_strdup(buffer));
}

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
		if ((str[i] == '\'' ||  str[i] == '"') && is_real_character(str, i))
		{
			new = ft_strjoin_and_free_2strings(new, remove_quoting(str, &i));
			continue;
		}
		else if (str[i] == '\\')
			i++;
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