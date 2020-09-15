/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_intern_var.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihwang <ihwang@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/07 13:01:13 by marvin            #+#    #+#             */
/*   Updated: 2020/09/15 20:54:29 by ihwang           ###   ########.fr       */
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

int	        check_intern_var_syntax(char *data, t_token *lst_tokens)
{
    t_token *last_token;

    last_token = NULL;
    last_token = get_the_last_token(lst_tokens);
    if (last_token != NULL && \
        last_token->type != TOKEN_SEMI && \
        last_token->type != TOKEN_AND_IF && \
        last_token->type != TOKEN_OR_IF)
        return (false);
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

char		*ft_set_intern_var(t_exe *c)
{
    char    *var;
    char    *copy_key;
    char    *combiend;

    copy_key = ft_strndup(c->av[0], (int)(ft_strchr(c->av[0], '=') - c->av[0]));
    if (g_var == NULL && (g_var = (char**)ft_memalloc(sizeof(char*) * 2)))
    {
        g_var[0] = (char*)ft_memalloc(PATH_MAX);
        g_var[0] = ft_strcpy(g_var[0], c->av[0]);
        g_var[0] = ft_strcat(g_var[0], c->av[1]);
    }
    else if ((var = get_var(copy_key, g_var, KEY)))
    {
        var = ft_strcpy(var, c->av[0]);
        var = ft_strcat(var, c->av[1]);
    }
    else
    {
        combiend = ft_strjoin(c->av[0], c->av[1]);
        g_var = add_env(combiend, g_var);
        ft_strdel(&combiend);
    }
    ft_strdel(&copy_key);
    return (ft_strdup("success"));
}