/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_analysis.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthan <dthan@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/06 14:00:01 by dthan             #+#    #+#             */
/*   Updated: 2021/03/07 02:42:24 by dthan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	init_syntax_service_struct(t_syntax_service *self, t_token *head)
{
	self->cur_tk = head;
	self->prev_tk = NULL;
}

int		syntax_analysis_service(t_token *token_stream)
{
	t_syntax_service instance;

	init_syntax_service_struct(&instance, token_stream);
	while (instance.cur_tk)
	{
		if (analyzing_pair_tokens(
			instance.cur_tk, instance.prev_tk) == EXIT_FAILURE)
			return (EXIT_FAILURE);
		instance.prev_tk = instance.cur_tk;
		instance.cur_tk = instance.cur_tk->next;
	}
	return (EXIT_SUCCESS);
}
