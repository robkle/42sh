/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parameter_expansion.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthan <dthan@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/08 03:24:07 by dthan             #+#    #+#             */
/*   Updated: 2021/01/25 07:45:01 by dthan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

char *replace_replace(char *target, char *needle, char *replacement)
{
	char buffer[1024];
	char *tmp;
	char *insert_point;
	char *p;

	ft_bzero(buffer, 1024);
	tmp = target;
	insert_point = &buffer[0];
	while(1) {
		p = ft_strstr(tmp, needle);
		if (p == NULL)
		{
			ft_strcpy(insert_point, tmp);
			break;
		}
		ft_memcpy(insert_point, tmp, p - tmp);
		insert_point += p - tmp;
		ft_memcpy(insert_point, replacement, ft_strlen(replacement));
		insert_point += ft_strlen(replacement);
		tmp = p + ft_strlen(needle);
	}
	return (strdup(buffer));
}

int jump_expansion(char *str, int *i, char expansion_type, char temp[2])
{
	int stack;
	char rev_type;

	rev_type = (expansion_type == '{') ? '}' : ')';
	stack = 0;
	while (str[++(*i)])
	{
		if (str[*i] == expansion_type)
			stack++;
		else if (str[*i] == rev_type)
			stack--;
		else if ((str[*i] == '"' || str[*i] == '\'' || str[*i] == '\\') && is_real_character(str, *i))
		{
			if (temp != NULL)
				temp[0] = str[*i];
			if (jump_quote(str, i, str[*i]) == EXIT_FAILURE)
				return (EXIT_FAILURE);
			if (temp != NULL)
				temp[0] = expansion_type;
		}
		if (stack == 0)
			break;
	}
	if (str[*i] == '\0')
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int is_parameter_expansion(char *str)
{
	int i;

	i = -1;
	while (str[++i])
		if (str[i] == '$' && is_real_character(str, i) && str[i + 1] && str[i + 1] == '{')
			return (1);
	return (0);
}

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

// int parameter_expansion_replace_av(char **av, int i)
// {
// 	char *temp;
// 	char *replacement;

// 	temp = av[i];
// 	replacement = ft_itoa(g_shell.exit_status);
// 	av[i] = replace_replace(temp, "${?}", replacement);
// 	free(replacement);
// 	free(temp);
// 	if (is_parameter_expansion(av[i]))
// 		return (EXIT_FAILURE);
// 	return (EXIT_SUCCESS);
// }

//

char *find_needle(char *str)
{
	int i;
	char buf[4096];
	int head;
	int tail;

	i = -1;
	head = 0;
	tail = 0;
	ft_bzero(buf, 4096);
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
	return (ft_strndup(&str[head], tail - head + 1));
}

char *parameter_expansion_simplest_form(char *str)
{
	t_var *var;
	var = NULL;

	if (ft_strequ("?", str))
		return (ft_itoa(g_shell.exit_status));
	if (is_intern_var(str))
		var = ft_getvar(str);
	else
		return ft_strnew(0);
	return (var->value) ? ft_strdup(var->value): ft_strnew(0);
}

int is_parameter_expansion_delimeter(char c)
{
	if (c == ':' || c == '=' || c == '-' || c == '?' || c == '+')
		return (1);
	return (0);
}

// void parameter_expansion_split(char *str, char parameter[256], char delimeter[3], char word[256])
// {
// 	int i;
// 	int j;

// 	i = 0;
// 	//parameter
// 	j = 0;
// 	while (str[i])
// 	{
// 		if (is_parameter_expansion_delimeter(str[i]))
// 			break;
// 		parameter[j++] = str[i++];
// 	}
// 	//delimeter
// 	j = 0;
// 	while (str[i])
// 	{
// 		if (!is_parameter_expansion_delimeter(str[i]))
// 			break;
// 		delimeter[j++] = str[i++];
// 	}
// 	//word
// 	j = 0;
	
// }

char *find_replacement(char *str)
{
	t_var *var;
	char parameter[256];
	char delimeter[2];
	char word[256];

	var = NULL;
	ft_bzero(parameter, 256);
	ft_bzero(delimeter, 3);
	ft_bzero(word, 256);
	// parameter_expansion_split(str, parameter, delimeter, word);
	if (ft_strlen(delimeter) == 0)
		return (parameter_expansion_simplest_form(str));
	// the complicated form
	return (parameter_expansion_simplest_form(str));
}

int parameter_expansion_syntax_analysis(char *str)
{
	int i;

	if (str == NULL || *str == '\0')
		return EXIT_FAILURE;
	i = -1;
	while (str[++i])
		if (!ft_isalnum(str[i]) && str[i] != ':' && str[i] != '-'
			&& str[i] != '=' && str[i] != '?' && str[i] != '+'
			&& str[i] != '#' && str[i] != '%')
			return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

// new
int parameter_expansion_replace_av(char **av, int i)
{
	char *temp;
	char *replacement;
	char *needle;
	char needle_buf[256];

	temp = av[i];
	needle = find_needle(temp);

	ft_bzero(needle_buf, 256);
	ft_strcpy(needle_buf, &needle[2]);
	needle_buf[ft_strlen(needle) - 2 - 1] = '\0';
	if (parameter_expansion_syntax_analysis(needle_buf) == EXIT_FAILURE)
	{
		ft_dprintf(2, "%s: %s: bad substitution\n", SHELL_NAME, needle);
		free(needle);
		return (EXIT_FAILURE);
	}
	replacement = find_replacement(needle_buf);
	av[i] = replace_replace(temp, needle, replacement);
	free(needle);
	free(replacement);
	free(temp);
	if (is_parameter_expansion(av[i]))
	 	return (parameter_expansion_replace_av(av, i));
	return (EXIT_SUCCESS);
}
//

// reordering av

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
