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

char		*ft_getvar(const char *name)
{
	char	*var;
	int		i;
	size_t	len;

	if ((var = ft_getenv(name)) != NULL)
		return (var);
	if (g_shell.var == NULL)
		return (NULL);
	i = -1;
	len = ft_strlen(name);
	while (g_shell.var[++i])
		if (ft_strnequ(name, g_shell.var[i], len) && g_shell.var[i][len] == '=')
			return (&g_shell.var[i][len + 1]);
	return (NULL);
}
