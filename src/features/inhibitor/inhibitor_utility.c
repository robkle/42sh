/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inhibitor_utility.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthan <dthan@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/31 17:12:19 by dthan             #+#    #+#             */
/*   Updated: 2021/01/28 16:23:03 by dthan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

char	*delete_line_feed_at_the_end_of_the_cmd_string(char *cmd)
{
	char *new;

	if (cmd == NULL)
		return NULL;
	new = ft_strndup(cmd, ft_strlen(cmd) - 1);
	free (cmd);
	return (new);	
}

int		jump_quote(char *input, int *i, char quote_type)
{
	if (quote_type == '\\')
		(*i)++;
	else if (quote_type == '"' || quote_type == '\'')
	{
		(*i)++;
		while (input[*i])
		{
			if (input[*i] == quote_type && is_real_character(input, *i))
				break;
			(*i)++;
		}
	}
	if (input[*i] == '\0')
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
