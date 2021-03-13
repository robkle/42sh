/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_tools.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthan <dthan@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/14 01:30:02 by dthan             #+#    #+#             */
/*   Updated: 2021/03/14 01:30:04 by dthan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

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
