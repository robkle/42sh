/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getenv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthan <dthan@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/25 17:40:20 by dthan             #+#    #+#             */
/*   Updated: 2020/12/25 17:41:37 by dthan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

char *ft_getenv(const char *name)
{
	int i;
	int len;

	if (name == NULL || g_shell.env == NULL)
		return (NULL);
	i = -1;
	len = ft_strlen(name);
	while (g_shell.env[++i])
		if (ft_strnequ(name, g_shell.env[i], len) && g_shell.env[i][len] == '=')
			return (&g_shell.env[i][len + 1]);
	return (NULL);
}
