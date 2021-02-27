/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parameter_expansion_tool2.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthan <dthan@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/27 11:55:59 by dthan             #+#    #+#             */
/*   Updated: 2021/02/27 15:31:40 by dthan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	substitute_parameter(char parameter[256], char replacement[256])
{
	char *temp;

	temp = NULL;
	if (ft_strequ("?", parameter))
	{
		temp = ft_itoa(g_shell.exit_status);
		ft_strcpy(replacement, temp);
		if (temp)
			free(temp);
		return ;
	}
	temp = ft_getvar(parameter)->value;
	ft_strcpy(replacement, temp);
}

void	substitute_word(char word[256], char replacement[256])
{
	ft_strcpy(replacement, word);
}

void	assign_word(char parameter[256], char word[256])
{
	t_var	*intern_var;
	t_var	*ptr;

	intern_var = (t_var*)ft_memalloc(sizeof(t_var));
	intern_var->name = ft_strdup(parameter);
	intern_var->value = ft_strdup(word);
	if (ft_getenv(intern_var->name))
		intern_var->exported = 1;
	else if ((ptr = ft_getvar(intern_var->name)) != NULL && ptr->exported == 1)
		intern_var->exported = 1;
	else
		intern_var->exported = 0;
	if (is_intern_var(intern_var->name))
		update_intern_var(intern_var);
	else
		add_intern_var(intern_var);
}




int number(char replacement[256], char ch)
{
	int i;

	i = -1;
	while (replacement[++i])
		if (replacement[i] == ch)
			return (i);
	return (-1);
}

int remove_smallest_prefix_pattern(char replacement[256], char word[256])
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
			j = number(replacement, word[++i]);
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

int number2(char replacement[256], char ch)
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

int remove_largest_prefix_pattern(char replacement[256], char word[256])
{
	int i;
	int j;

	i = -1;
	j = 0; // maybe dont need this line
	while (word[++i])
	{
		if (word[i] == '*' && word[i + 1] == '*')
			continue;
		if (word[i] == '*' && word[i + 1] == '\0')
			replacement[0] = '\0';
		else if (word[i] == '*' && word[i + 1] != '*')
		{
			j = number2(replacement, word[++i]);
			if (j == -1)
				return (EXIT_FAILURE);
			ft_strcpy(replacement, &replacement[j + 1]);
		}
		else if (word[i] == '*' && word[i + 1] == '\0')
			replacement[0] = '\0';
		else if (word[i] == replacement[0])
			ft_strcpy(replacement, &replacement[1]);
		else
			return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

void	remove_smallest_or_largest_prefix_pattern(char parameter[256],
		char word[256], char replacement[256], char delimeter[3])
{
	char orig[256];

	ft_bzero(orig, 256);
	substitute_parameter(parameter, replacement);
	ft_strcpy(orig, replacement);
	if (ft_strequ(delimeter, "#"))
	{
		if (remove_smallest_prefix_pattern(replacement, word) == EXIT_FAILURE)
			ft_strcpy(replacement, orig);
	}
	else
	{
		if (remove_largest_prefix_pattern(replacement, word) == EXIT_FAILURE)
			ft_strcpy(replacement, orig);
	}
}


// int number3(char replacement[256], char ch)
// {
// 	int i;

// 	i = ft_strlen(replacement);
// 	while (--i >= 0)
// 		if (replacement[i] == ch)
// 			return (i);
// 	return (-1);
// }

// int remove_smallest_suffix_pattern(char replacement[256], char word[256])
// {
// 	int i;
// 	int j;

// 	i = ft_strlen(word);
// 	while (i-- >= 0)
// 	{
// 		if (word[i] == '*' && i == 0)
// 			replacement[0] == '\0';
// 		else if (word[i] == '*' && i > 0 && word[i - 1] == '*')
// 			continue;
// 		else if (word[i] == '*' && i > 0 && word[i - 1] != '*')
// 		{
// 			j = number3(replacement, word[i - 1]);
// 			if (j == -1)
// 				return (EXIT_FAILURE);
// 			replacement[j] = '\0';
// 		}
// 		else if (word[i] == replacement[ft_strlen(replacement) - 1])
// 			replacement[ft_strlen(replacement) - 1] = '\0';
// 		// else if word[i] == '*' && i == 0
// 		else
// 			return (EXIT_FAILURE);
// 	}
// 	return (EXIT_SUCCESS);
// }

int remove_smallest_suffix_pattern(char replacement[256], char word[256])
{
	ft_strrev(replacement);
	ft_strrev(word);
	if (remove_smallest_prefix_pattern(replacement, word) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	ft_strrev(replacement);
	return (EXIT_SUCCESS);
}

int remove_largest_suffix_pattern(char replacement[256], char word[256])
{
	ft_strrev(replacement);
	ft_strrev(word);
	if (remove_largest_prefix_pattern(replacement, word) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	ft_strrev(replacement);
	return (EXIT_SUCCESS);
}

// int remove_largest_suffix_pattern(char replacement[256], char word[256])
// {
// 	int i;

// 	i = -1;
// 	while (word[++i])
// 	{

// 	}
// 	return (EXIT_SUCCESS);
// }

void	remove_smallest_or_largest_suffix_pattern(char parameter[256],
		char word[256], char replacement[256], char delimeter[3])
{
	// int i;
	char orig[256];

	ft_bzero(orig, 256);
	substitute_parameter(parameter, replacement);
	ft_strcpy(orig, replacement);
	if (ft_strequ(delimeter, "%"))
	{
		if (remove_smallest_suffix_pattern(replacement, word) == EXIT_FAILURE)
			ft_strcpy(replacement, orig);
	}
	else
	{
		if (remove_largest_suffix_pattern(replacement, word) == EXIT_FAILURE)
			ft_strcpy(replacement, orig);
	}
}


