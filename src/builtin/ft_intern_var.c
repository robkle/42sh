/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_intern_var.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihwang <ihwang@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/07 13:01:13 by marvin            #+#    #+#             */
/*   Updated: 2020/10/10 17:33:50 by ihwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "builtin.h"

char		*ft_set_intern_var(t_process *c)
{
    char    *var;
    char    *copy_key;
    char    *combiend;

    copy_key = ft_strndup(c->av[0], (int)(ft_strchr(c->av[0], '=') - c->av[0]));
    if (g_shell.var == NULL && \
        (g_shell.var = (char**)ft_memalloc(sizeof(char*) * 2)))
    {
        g_shell.var[0] = (char*)ft_memalloc(PATH_MAX);
        g_shell.var[0] = ft_strcpy(g_shell.var[0], c->av[0]);
        g_shell.var[0] = ft_strcat(g_shell.var[0], c->av[1]);
    }
    else if ((var = get_var(copy_key, g_shell.var, KEY)))
    {
        var = ft_strcpy(var, c->av[0]);
        var = ft_strcat(var, c->av[1]);
    }
    else
    {
        combiend = ft_strjoin(c->av[0], c->av[1]);
        g_shell.var = add_env(combiend, g_shell.var);
        ft_strdel(&combiend);
    }
    ft_strdel(&copy_key);
    return (ft_strdup("success"));
}