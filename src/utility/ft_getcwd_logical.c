/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getcwd_logical.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihwang <ihwang@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/04 15:12:46 by ihwang            #+#    #+#             */
/*   Updated: 2021/02/04 15:17:15 by ihwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

/*
**	The return value from this function shouldn't be freed until the whole
**	shell program ends
*/

char			*ft_getcwd_logical(void)
{
	char		*pwd;
	t_stat		lg;
	t_stat		phy;

	if ((pwd = ft_getenv("PWD")) == NULL)
		return (NULL);
	if (stat(pwd, &lg) == -1 || stat(".", &phy) == -1)
		return (NULL);
	if (lg.st_dev != phy.st_dev || lg.st_ino != phy.st_ino)
		return (NULL);
	return (pwd);
}

