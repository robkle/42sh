/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_the_last_token.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihwang <ihwang@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/08 12:34:49 by marvin            #+#    #+#             */
/*   Updated: 2020/10/10 17:52:50 by ihwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "token.h"

t_token     *get_the_last_token(t_token *lst_tokens)
{
    if (lst_tokens == NULL)
        return (NULL);
    while (lst_tokens->next)
        lst_tokens = lst_tokens->next;
    return (lst_tokens);
}
