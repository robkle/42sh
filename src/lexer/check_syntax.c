/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_syntax.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihwang <ihwang@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/02 15:22:31 by tango             #+#    #+#             */
/*   Updated: 2020/10/10 17:41:40 by ihwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "token.h"

t_token		*breakdown_node_for_intern_var(t_token *node)
{
    int     tail;
    t_token *leader;
    t_token *follower;

    tail = 1;
    while (node->data[tail] != '=')
        ++tail;
    leader = get_token(ft_strndup(node->data, tail + 1), 0);
    follower = get_token(ft_strdup(&node->data[tail + 1]), 0);
    ft_strdel(&node->data);
    free (node);
    leader->next = follower;
    return (leader);
}

int			check_intern_var_syntax(char *data, t_token *lst_tokens)
{
    t_token *last_token;

    last_token = NULL;
    last_token = get_the_last_token(lst_tokens);
    if (last_token != NULL && \
        last_token->type != TOKEN_SEMI && \
        last_token->type != TOKEN_AND_IF && \
        last_token->type != TOKEN_OR_IF)
        return (FALSE);
    if (!ft_isalpha(*data))
        return (FALSE);
    while (*data != '=' && *data != '\0')
    {
        if (!ft_isalnum(*data))
            return (FALSE);
        ++data;
    }
    if (*data == '\0')
        return (FALSE);
    return (TRUE);
}

int			check_syntax(t_token *lst_tokens)
{
	t_token	*ptr;
	char	buf[3];

	ptr = lst_tokens;
	ft_bzero(buf, 3);
	if (ptr && ptr->type == TOKEN_SEMI)
	{
		return (error_monitor(SYNTAX_UNEXPECTED_TOKEN, ";", "'", 1));
	}
	while (ptr)
	{
		if (ptr->type == TOKEN_WORD && (is_separator_operator(ptr->data, 0) \
					|| is_redirection_operator(ptr->data, 0)))
		{
			return (error_monitor(SYNTAX_UNEXPECTED_TOKEN,\
			ft_strncpy(buf, ptr->data, 2), "'", 1));
		}
		ptr = ptr->next;
	}
	return (EXIT_SUCCESS);
}
