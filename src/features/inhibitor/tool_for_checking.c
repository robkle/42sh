/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tool_for_checking.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthan <dthan@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/04 06:21:11 by dthan             #+#    #+#             */
/*   Updated: 2020/12/31 18:23:50 by dthan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

// need to improve this
int	is_open_dquote(char *input, int level, char *quote)
{
	int matched;
	int i;

	i = 0;
	matched = 0;
	while (input[i] && *quote == '\0')
	{
		if ((input[i] == '"' || input[i] == '\'') && is_real_quote(input, i))		
		{
			matched++;
			*quote = input[i];
		}
		i++;
	}
	while (input[i])
	{
		if ((input[i] == *quote) && is_real_quote(input, i))		
			matched++;
		i++;
	}
	if (level == 1)
		return (((matched % 2) == 0) ? EXIT_SUCCESS : EXIT_FAILURE);
	return (((matched % 2) == 0) ? EXIT_FAILURE : EXIT_SUCCESS);
}

int is_open_back_slash(char *input)
{
	int i;
	int matches;

	if (input == NULL)
		return (0);
	i = ft_strlen(input) - 2;
	matches = 0;
	if (input[i] == '\\')
	{
		matches = 1;
		while (--i >= 0 && input[i] == '\\')
			matches++;
	}
	return (matches % 2) == 1 ? 1 : 0;
}
