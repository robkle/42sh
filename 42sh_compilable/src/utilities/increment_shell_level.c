/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   increment_shell_level.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihwang <ihwang@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/02 17:56:58 by tango             #+#    #+#             */
/*   Updated: 2020/09/15 21:12:22 by ihwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void		increment_shlvl(void)
{
	char	*shlvl;
	int		nb;
	char	*ascii;

	shlvl = get_var("SHLVL", g_env, VAL);
	nb = ft_atoi(shlvl);
	nb++;
	ascii = ft_itoa(nb);
	ft_strcpy(shlvl, ascii);
	ft_strdel(&ascii);
}
