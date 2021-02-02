/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_var.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthan <dthan@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/06 14:49:46 by ihwang            #+#    #+#             */
/*   Updated: 2021/01/28 16:24:35 by dthan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

char	*get_var(char *name, char **lst_var, int keyval)
{
	int		i;
	int		len;

	i = -1;
	len = ft_strlen(name);
	while (lst_var[++i])
	{
		if (keyval == VAL)
		{
			if (ft_strnequ(lst_var[i], name, len) && \
				name[0] == lst_var[i][0] && lst_var[i][len] == '=')
				return (&lst_var[i][len + 1]);
		}
		else
		{
			if (ft_strnequ(lst_var[i], name, len) && \
				name[0] == lst_var[i][0] && lst_var[i][len] == '=')
				return (lst_var[i]);
		}
	}
	return (NULL);
}
