/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   complex_parameter_expansion4.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthan <dthan@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/28 13:03:27 by dthan             #+#    #+#             */
/*   Updated: 2021/02/28 14:02:30 by dthan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static int	find_the_smallest_prefix_pattern(char replacement[256], char ch)
{
	int i;

	i = -1;
	while (replacement[++i])
		if (replacement[i] == ch)
			return (i);
	return (-1);
}

int			remove_smallest_prefix_pattern(
	char replacement[256], char word[256])
{
	int i;
	int j;

	i = -1;
	j = 0;
	while (word[++i])
	{
		if (word[i] == '*' && (word[i + 1] == '*' || word[i + 1] == '\0'))
			continue;
		if (word[i] == '*' && word[i + 1] != '*')
		{
			j = find_the_smallest_prefix_pattern(replacement, word[++i]);
			if (j == -1)
				return (EXIT_FAILURE);
			ft_strcpy(replacement, &replacement[j + 1]);
		}
		else if (word[i] == replacement[0])
			ft_strcpy(replacement, &replacement[1]);
		else
			return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

static int	find_the_largest_prefix_pattern(char replacement[256], char ch)
{
	int i;
	int saved_pos;

	i = -1;
	saved_pos = -1;
	while (replacement[++i])
		if (replacement[i] == ch)
			saved_pos = i;
	return (saved_pos);
}

int			remove_largest_prefix_pattern(char replacement[256], char word[256])
{
	int i;
	int j;

	i = -1;
	j = 0;
	while (word[++i])
	{
		if (word[i] == '*' && word[i + 1] == '*')
			continue;
		if (word[i] == '*' && word[i + 1] == '\0')
			replacement[0] = '\0';
		else if (word[i] == '*' && word[i + 1] != '*')
		{
			j = find_the_largest_prefix_pattern(replacement, word[++i]);
			if (j == -1)
				return (EXIT_FAILURE);
			ft_strcpy(replacement, &replacement[j + 1]);
		}
		else if (word[i] == replacement[0])
			ft_strcpy(replacement, &replacement[1]);
		else
			return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

void		remove_smallest_or_largest_prefix_pattern(
	t_parameter_expansion *self
)
{
	char orig[256];

	ft_bzero(orig, 256);
	substitute_parameter(self->parameter, self->replacement);
	ft_strcpy(orig, self->replacement);
	if (ft_strequ(self->delimeter, "#"))
	{
		if (remove_smallest_prefix_pattern(
			self->replacement, self->word) == EXIT_FAILURE)
			ft_strcpy(self->replacement, orig);
	}
	else
	{
		if (remove_largest_prefix_pattern(
			self->replacement, self->word) == EXIT_FAILURE)
			ft_strcpy(self->replacement, orig);
	}
}
