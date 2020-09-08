/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_intern_var.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihwang <ihwang@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/07 13:01:13 by marvin            #+#    #+#             */
/*   Updated: 2020/09/08 13:24:08 by ihwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

t_token     *breakdown_node_for_intern_var(t_token *node)
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

int	        check_intern_var_syntax(t_token *node, t_token *lst_tokens)
{
    t_token *last_token;
    char    *data;

    last_token = NULL;
    last_token = get_the_last_token(lst_tokens);
    if (last_token != NULL && \
        last_token->type != TOKEN_SEMI && \
        last_token->type != TOKEN_AND_IF && \
        last_token->type != TOKEN_OR_IF)
        return (false);
    data = node->data;
    if (!ft_isalpha(*data))
        return (false);
    while (*data != '=' && *data != '\0')
    {
        if (!ft_isalnum(*data))
            return (false);
        ++data;
    }
    if (*data == '\0')
        return (false);
    return (true);
}

/*
int						ft_set_intern_var(t_exe *c)
{
    (void)c;

    return (0);
}
*/