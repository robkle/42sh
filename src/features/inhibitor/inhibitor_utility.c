/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inhibitor_utility.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthan <dthan@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/31 17:12:19 by dthan             #+#    #+#             */
/*   Updated: 2021/01/07 19:24:00 by dthan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
/*
static int count_backslash(char range[3])
{
	int i;
	int ct;

	i = 3  ;
	ct = 0;
	while (--i >= 0)
	{
		if (range[i] && range[i] == '\\')
			ct++;
		else
			ct = 0;
	}
	return (ct);
}
*/
int is_real_quote(char *str, int i)
{
	int ct;

	if (i == 0)
		return (1);
	ct = 0;
	while (i-- >= 0 && str[i] == '\\')
		ct++;
	if (ct % 2 == 0)
		return (1);
	return (0);
}

char *delete_line_feed_at_the_end_of_the_cmd_string(char *cmd)
{
	char *new;

	if (cmd == NULL)
		return NULL;
	new = ft_strndup(cmd, ft_strlen(cmd) - 1);
	free (cmd);
	return (new);	
}
