/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linebreak.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthan <dthan@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/06 13:30:31 by dthan             #+#    #+#             */
/*   Updated: 2021/03/06 13:36:28 by dthan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void linebreak(t_token **token)
{
	(*token) = (*token)->next;
	if (*token != NULL && (*token)->type == TOKEN_NEWLINE)
		linebreak(token);
}
