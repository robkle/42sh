/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear_token.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthan <dthan@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/02 17:56:39 by tango             #+#    #+#             */
/*   Updated: 2020/10/05 04:02:20 by dthan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	clear_token(t_token *token)
{
	t_token *temp;

	while (token)
	{
		ft_strdel(&token->data);
		temp = token;
		token = token->next;
		free(temp);
	}
}
