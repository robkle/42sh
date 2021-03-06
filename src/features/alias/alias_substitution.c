/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alias_substitution.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthan <dthan@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/15 23:35:55 by vgrankul          #+#    #+#             */
/*   Updated: 2021/03/06 16:12:02 by dthan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

char	*find_alias_str(char *str)
{
	int i;

	i = 0;
	while (g_shell.alias[i] != NULL)
	{
		if (ft_strequ(g_shell.alias[i]->name, str))
			return (g_shell.alias[i]->value);
		i++;
	}
	return (NULL);
}

int	is_alias(char *str, t_token *prev_token)
{
	int i;

	i = 0;
	if (prev_token && !is_control_op_not_newline(prev_token->type))
		return (0);
	if (g_shell.alias != NULL)
	{
		while (g_shell.alias[i] != NULL)
		{
			if (ft_strequ(g_shell.alias[i]->name, str))
				return (1);
			i++;
		}	
	}
	return (0);
}

int token_stream_length(t_token *lst)
{
	int ct;

	ct = 0;
	while (lst)
	{
		lst = lst->next;
		ct++;
	}
	return (ct);
}

t_token *find_current_token_in_new_stream(t_token *tk_lst)
{
	t_token *current_tk;
	t_token *temp;

	temp = tk_lst;
	if (tk_lst == NULL)
		return (NULL);
	while (temp)
	{
		current_tk = temp;
		temp = temp->next;
	}
	return (current_tk);
}

t_token *find_prev_token_in_new_stream(t_token *tk_lst)
{
	t_token *prev_tk;
	t_token *temp;

	temp = tk_lst;
	if (tk_lst == NULL || tk_lst->next == NULL)
		return (NULL);
	while (temp->next)
	{
		prev_tk = temp;
		temp = temp->next;
	}
	return (prev_tk);
}

void	alias_substitution(t_token **cur_tk, t_token **prev_tk, char *prev_alias)
{
	t_token *new_stream;
	char *alias;

	new_stream = NULL;
	alias = find_alias_str((*cur_tk)->data);
	new_stream = lexical_analysis_service(alias, (prev_alias) ? (prev_alias) : alias, (ft_strnequ((*cur_tk)->data, alias, ft_strlen((*cur_tk)->data))) ? 1 : 0);
	if (new_stream != NULL)
	{
		if (token_stream_length(new_stream) > 1)
		{
			clear_token((*cur_tk));
			(*cur_tk) = find_current_token_in_new_stream(new_stream);
			(*prev_tk) = find_prev_token_in_new_stream(new_stream);
		}
		else
		{
			clear_token(*cur_tk);
			*cur_tk = find_current_token_in_new_stream(new_stream);
		}
	}
	else
	{
		clear_token((*cur_tk));
		*cur_tk = NULL;
	}
}
