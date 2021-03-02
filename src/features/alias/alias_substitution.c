/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alias_substitution.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthan <dthan@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/15 23:35:55 by vgrankul          #+#    #+#             */
/*   Updated: 2021/02/04 23:39:49 by dthan            ###   ########.fr       */
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

void	alias_substitution(t_token **current_token, t_token **prev_token, t_token **tk_lst)
{	

	t_token *new_stream;

	new_stream = NULL;
	lexical_analysis_and_syntax_analysis(find_alias_str((*current_token)->data),
	&new_stream, LEX_CMD, 1);
	if (new_stream != NULL)
	{
		add_token_into_token_list(tk_lst, new_stream);
		if (token_stream_length(new_stream) > 1)
		{
			clear_token((*current_token));
			(*current_token) = find_current_token_in_new_stream((*tk_lst));
			(*prev_token) = find_prev_token_in_new_stream((*tk_lst));
		}
		else if (token_stream_length(new_stream) == 1)
		{
			clear_token((*current_token));
			(*current_token) = find_current_token_in_new_stream((*tk_lst));
		}		
	}
	else
	{
		clear_token((*current_token));
		*current_token = NULL;
	}		
}
