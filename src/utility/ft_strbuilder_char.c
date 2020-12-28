/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strbuilder_char.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthan <dthan@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/25 18:12:27 by dthan             #+#    #+#             */
/*   Updated: 2020/12/25 18:13:02 by dthan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

char *ft_strbuilder_char(char *old, char c)
{
	char *new;
	int len;

	len = ft_strlen(old);
	new = ft_strnew(len + 1);
	new = ft_strcpy(new, old);
	new[len] = c;
	free(old);
	return (new);
}
