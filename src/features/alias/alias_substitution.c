/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alias_substitution.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthan <dthan@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/15 23:35:55 by vgrankul          #+#    #+#             */
/*   Updated: 2021/03/09 07:59:50 by dthan            ###   ########.fr       */
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

// find alias, so we can get it name and value and pass to lexical_analysis_service

t_alias *find_alias2(char *str)
{
	int i;

	i = 0;
	while (g_shell.alias[i] != NULL)
	{
		if (ft_strequ(g_shell.alias[i]->name, str))
			return (g_shell.alias[i]);
		i++;
	}
	return (NULL);
}

void	alias_substitution(t_lexical_service *lex, char *fix_alias_name)
{
	t_token *new_stream;
	t_alias *alias;

	new_stream = NULL;
	alias = find_alias2(lex->tk->data);
	new_stream = lexical_analysis_service(alias->value, fix_alias_name, (ft_strnequ(lex->tk->data , alias->value, ft_strlen(lex->tk->data))) ? 1 : 0);
	if (new_stream != NULL)
	{
		if (token_stream_length(new_stream) > 1)
		{
			clear_token(lex->tk);
			lex->tk = find_current_token_in_new_stream(new_stream);
			lex->prev_tk = find_prev_token_in_new_stream(new_stream);
		}
		else
		{
			clear_token(lex->tk);
			lex->tk = find_current_token_in_new_stream(new_stream);
		}
	}
	else
	{
		clear_token(lex->tk);
		lex->tk = NULL;
	}
	// add_token_into_token_list(&(lex->stream), new_stream);
	if (alias->value[ft_strlen(alias->value) - 1] == ' ' ||
		alias->value[ft_strlen(alias->value) - 1] == '\t')
		lex->keep_alias_substitution = 1;
	else
		lex->keep_alias_substitution = 0;
}
