/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inhibitor_utility.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthan <dthan@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/31 17:12:19 by dthan             #+#    #+#             */
/*   Updated: 2021/01/25 07:40:42 by dthan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

char *delete_line_feed_at_the_end_of_the_cmd_string(char *cmd)
{
	char *new;

	if (cmd == NULL)
		return NULL;
	new = ft_strndup(cmd, ft_strlen(cmd) - 1);
	free (cmd);
	return (new);	
}
