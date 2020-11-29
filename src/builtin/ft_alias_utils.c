/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_alias_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgrankul <vgrankul@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/15 23:35:55 by vgrankul          #+#    #+#             */
/*   Updated: 2020/10/05 04:14:12 by vgrankul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "../includes/libft.h"

char	*set_value(char *argv)
{
	int		i;
	char	*value;

	i = 0;
	while (argv[i] != '\0' && argv[i] != '=')
		i++;
	ft_strtrim_d_quote(value = ft_strsub(argv, i + 1, ft_strlen(argv) - (i + 1)));
	return (value);
}

char	*set_name(char *argv)
{
	int		i;
	char	*name;

	i = 0;
	while (argv[i] != '\0' && argv[i] != '=')
		i++;
	name = ft_strsub(argv, 0, i);
	return (name);
}