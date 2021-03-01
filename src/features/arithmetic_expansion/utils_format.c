/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_format.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rklein <rklein@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/26 16:07:23 by rklein            #+#    #+#             */
/*   Updated: 2021/02/26 16:08:40 by rklein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	ft_free_link(t_st *link)
{
	free(link->op);
	free(link->type);
	free(link);
}

void	ft_arx_skip_link(t_st *infix)
{
	if (infix->next)
		infix->next->prev = infix->prev;
	infix->prev->next = infix->next;
}
