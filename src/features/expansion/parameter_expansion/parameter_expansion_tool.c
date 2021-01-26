/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parameter_expansion_tool.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthan <dthan@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/26 07:00:23 by dthan             #+#    #+#             */
/*   Updated: 2021/01/26 07:09:58 by dthan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

char *parameter_expansion_tool_replace(char *target, char *needle, char *replacement)
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

void substitute_parameter(char parameter[256], char replacement[256])
{
	char *temp;

	temp = NULL;
	if (ft_strequ("?", parameter))
	{
		temp = ft_itoa(g_shell.exit_status);
		ft_strcpy(replacement, temp);
		if (temp)
			free(temp);
		return;
	}
	temp = ft_getvar(parameter)->value;
	ft_strcpy(replacement, temp);
}

void substitute_word(char word[256], char replacement[256])
{
	ft_strcpy(replacement, word);
}

void assign_word(char parameter[256], char word[256])
{
	t_var *intern_var;
	t_var *ptr;

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
