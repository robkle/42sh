/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alias_substitution.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthan <dthan@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/15 23:35:55 by vgrankul          #+#    #+#             */
/*   Updated: 2021/01/06 17:45:22 by dthan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

/*
void	update_tokens_with_alias(t_token *current_token,
t_token **prev_token, t_token **token_lst, char *alias_substr)
{
	t_token *lst;

	lst = NULL;
	free(g_shell.last_alias);
	g_shell.last_alias = ft_strdup(current_token->data);
	clear_token(current_token);
	if (ft_strlen(alias_substr) != 0)
	{
		lst = lexer_and_parser(alias_substr);
		while (lst != NULL)
		{
			add_token_into_token_list(token_lst, lst);
			if (!parser(lst, *(prev_token)))
				clear_token(lst);
			*prev_token = lst;
			lst = lst->next;
		}
		print_token(*token_lst);
	}
}
*/
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
	while (g_shell.alias[i] != NULL)
	{
		if (ft_strequ(g_shell.alias[i]->name, str))
			return (1);
		i++;
	}
	return (0);
}

// int		alias_substitution(t_token *current_token,
// t_token **prev_token, t_token **token_lst)
// {
// 	char	*alias_substr;

// 	alias_substr = NULL;
// 	if (g_shell.last_alias != NULL &&
// 	ft_strcmp(g_shell.last_alias, current_token->data) == 0)
// 		return (0);
// 	if ((*prev_token) == NULL || ((*prev_token) != NULL &&
// 	is_control_op_not_newline((*prev_token)->type) == 1))
// 	{
// 		if (g_shell.last_alias != NULL)
// 			free(g_shell.last_alias);
// 		g_shell.last_alias = NULL;
// 		if ((alias_substr = is_alias(current_token->data)) != NULL)
// 		{
// 			update_tokens_with_alias(current_token,
// 			prev_token, token_lst, alias_substr);
// 			return (1);
// 		}
// 	}
// 	return (0);
// }

// new

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

	if (tk_lst == NULL)
		return (NULL);
	while (tk_lst)
	{
		current_tk = tk_lst;
		tk_lst = tk_lst->next;
	}
	return (current_tk);
}

t_token *find_prev_token_in_new_stream(t_token *tk_lst)
{
	t_token *prev_tk;

	if (tk_lst == NULL || tk_lst->next == NULL)
		return (NULL);
	while (tk_lst->next)
	{
		prev_tk = tk_lst;
		tk_lst = tk_lst->next;
	}
	return (prev_tk);
}

void	alias_substitution(t_token **current_token, t_token **prev_token, t_token **tk_lst)
{
	t_token *new_stream;
	t_token *prev_token_temp;
	t_token *current_token_temp;

	new_stream = NULL;
	prev_token_temp = *current_token;
	current_token_temp = *prev_token;
	lexical_analysis_and_syntax_analysis(find_alias_str((*current_token)->data), &new_stream);
	if (new_stream != NULL)
	{
		if (token_stream_length(new_stream) > 1)
		{
			current_token_temp = find_current_token_in_new_stream(new_stream);
			prev_token_temp = find_prev_token_in_new_stream(new_stream);
			clear_token(*current_token);
			clear_token(*prev_token);
			*current_token = current_token_temp;
			*prev_token = prev_token_temp;
		}
		else if (token_stream_length(new_stream) == 1)
		{
			clear_token(*current_token);
			*current_token = current_token_temp;
		}
		add_token_into_token_list(tk_lst, new_stream);
	}
	else
	{
		clear_token(*current_token);
		*current_token = NULL;
	}
}
