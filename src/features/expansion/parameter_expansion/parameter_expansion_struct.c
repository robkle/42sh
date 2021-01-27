/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parameter_expansion_struct.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthan <dthan@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/26 06:53:19 by dthan             #+#    #+#             */
/*   Updated: 2021/01/27 07:39:53 by dthan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void parameter_expansion_struct_valid_delimeter(char ***valid_delimeter)
{
	static char *delimeter[5];

	if (!ft_strequ(delimeter[0], ":-"))
	{
		delimeter[0] = ":-";
		delimeter[1] = ":=";
		delimeter[2] = ":?";
		delimeter[3] = ":+";
		delimeter[4] = NULL;
	}
	*valid_delimeter = delimeter;
}

void parameter_expansion_struct_needle(char needle[256], char *str)
{
	int i;
	int head;
	int tail;

	i = -1;
	head = 0;
	tail = 0;
	while (str[++i])
	{
		if ((str[i] == '$' && is_real_character(str, i)) && str[i + 1] && str[i + 1] == '{')
		{
			head = i;
			jump_expansion(str, &i, str[i + 1], NULL);
			tail = i;
			break;
		}
	}
	i = 0;
	while(head <= tail)
		needle[i++] = str[head++];
}

void parameter_expansion_struct_expression(char expression[256], char needle[256])
{
	ft_strcpy(expression, &needle[2]);
	expression[ft_strlen(expression) - 1] = '\0';
}

int is_valid_parameter_expansion_delimeter(char *buf, char **valid_delimeters)
{
	int i;

	i = -1;
	while (valid_delimeters[++i])
		if (ft_strequ(buf, valid_delimeters[i]))
			return (1);
	return (0);
}

void parameter_expansion_struct_split(t_parameter_expansion *self)
{
	int i;

	i = -1;
	while (self->expression[++i])
	{
		if (self->expression[i] == ':' && self->expression[i + 1])
		{
			ft_strncpy(self->delimeter, &(self->expression[i]), 2);
			if (is_valid_parameter_expansion_delimeter(self->delimeter, self->valid_delimeter))
			{
				i += 2;
				ft_strcpy(self->word, &(self->expression[i]));
				break;
			}
			ft_bzero(self->delimeter, 3);
		}
		else if (i > 0 && self->expression[i] == '#')
		{
			self->delimeter[0] = '#';
			i++;
			if (self->expression[i] && self->expression[i] == '#')
			{
				self->delimeter[1] = '#';
				i++;
			}
			ft_strcpy(self->word, &(self->expression[i]));
			break;
		}
		else if (self->expression[i] == '%')
		{
			self->delimeter[0] = '%';
			i++;
			if (self->expression[i] && self->expression[i] == '%')
			{
				self->delimeter[1] = '%';
				i++;
			}
			ft_strcpy(self->word, &(self->expression[i]));
			break;
		}
		self->parameter[i] = self->expression[i];
	}
}

int parameter_expansion_syntax_analysis(t_parameter_expansion *self)
{
	if (ft_strlen(self->expression) == 0)
		return (EXIT_FAILURE);
	if (ft_strlen(self->parameter) == 0)
		return (EXIT_FAILURE);
	if (self->parameter[0] == '#' && ft_strlen(self->delimeter) != 0)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int simple_parameter_expansion(char replacement[256], char parameter[256])
{
	char *temp;
	t_var *var;

	temp = NULL;
	var = NULL;
	if (ft_strequ("?", parameter))
	{
		temp = ft_itoa(g_shell.exit_status);
		ft_strcpy(replacement, temp);
		free(temp);
	}
	else if (parameter[0] == '#')
	{
		temp = ft_itoa(ft_strlen(&parameter[1]));
		ft_strcpy(replacement, temp);
		free(temp);
	}
	else if (is_intern_var(parameter))
	{
		var = ft_getvar(parameter);
		if (var->value)
			ft_strcpy(replacement, var->value);
	}
	return (EXIT_SUCCESS);
}

t_parameter_expansion_type find_parameter_replacement_type(char parameter[256])
{
	t_var *var;

	var = NULL;
	if (ft_strequ("?", parameter))
		return (PE_SET_AND_NOT_NULL);
	else if (is_intern_var(parameter))
	{
		var = ft_getvar(parameter);
		if (var->value)
			return (PE_SET_AND_NOT_NULL);
		return (PE_SET_BUT_NULL);
	}
	return (PE_UNSET);
}

int complex_parameter_expansion(char replacement[256], char parameter[256], char delimeter[3], char word[256])
{
	t_parameter_expansion_type type;

	type = find_parameter_replacement_type(parameter);
	if (ft_strequ(delimeter, ":-"))
	{
		if (type == PE_SET_AND_NOT_NULL)
			substitute_parameter(parameter, replacement);
		else if (type == PE_SET_BUT_NULL || type == PE_UNSET)
			substitute_word(word, replacement);
	}
	else if (ft_strequ(delimeter, ":="))
	{
		if (type == PE_SET_AND_NOT_NULL)
			substitute_parameter(parameter, replacement);
		else if (type == PE_SET_BUT_NULL || type == PE_UNSET)
		{
			assign_word(parameter, word);
			ft_strcpy(replacement, word);
		}
	}
	else if (ft_strequ(delimeter, ":?"))
	{
		if (type == PE_SET_AND_NOT_NULL)
			substitute_parameter(parameter, replacement);
		else if (type == PE_SET_BUT_NULL || type == PE_UNSET)
		{
			ft_dprintf(2, "%s: %s: %s\n", SHELL_NAME, parameter, word);
			return (EXIT_FAILURE);
		}
	}
	else if (ft_strequ(delimeter, ":+"))
	{
		if (type == PE_SET_AND_NOT_NULL)
			substitute_parameter(word, replacement);
	}
	else if (ft_strequ(delimeter, "%") || ft_strequ(delimeter, "%%"))
	{
		if (type == PE_SET_AND_NOT_NULL)
			remove_smallest_or_largest_suffix_pattern(parameter, word, replacement);
	}
	else if (ft_strequ(delimeter, "#") || ft_strequ(delimeter, "##"))
	{
		if (type == PE_SET_AND_NOT_NULL)
			remove_smallest_or_largest_prefix_pattern(parameter, word, replacement);
	}
	return (EXIT_SUCCESS);
}

int parameter_expansion_struct_replacement(char replacement[256], t_parameter_expansion *self)
{
	if (ft_strlen(self->delimeter) == 0)
		return (simple_parameter_expansion(replacement, self->parameter));
	return (complex_parameter_expansion(replacement, self->parameter, self->delimeter, self->word));
}

void destructor_parameter_expansion_struct(t_parameter_expansion *self)
{
	if (self == NULL)
		return;
	free(self);
}

t_parameter_expansion *constructor_parameter_expansion_struct(char *str)
{
	t_parameter_expansion *self;

	self = (t_parameter_expansion*)ft_memalloc(sizeof(t_parameter_expansion));
	parameter_expansion_struct_valid_delimeter(&self->valid_delimeter);
	parameter_expansion_struct_needle(self->needle, str);
	parameter_expansion_struct_expression(self->expression, self->needle);
	parameter_expansion_struct_split(self);
	if (parameter_expansion_syntax_analysis(self) == EXIT_FAILURE)
	{
		ft_dprintf(2, "%s: %s: bad substitution\n", SHELL_NAME, self->needle);
		destructor_parameter_expansion_struct(self);
		return (NULL);
	}
	if (parameter_expansion_struct_replacement(self->replacement, self) == EXIT_FAILURE)
	{
		destructor_parameter_expansion_struct(self);
		return (NULL);
	}
	return (self);
}
