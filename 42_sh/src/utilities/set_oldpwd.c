/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_oldpwd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihwang <ihwang@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/02 16:11:35 by tango             #+#    #+#             */
/*   Updated: 2020/09/06 15:22:09 by ihwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int			set_oldpwd(char pwd[PATH_MAX])
{
	t_exe	*cmd;

	if ((getcwd(pwd, PATH_MAX)) == NULL)
		return (EXIT_FAILURE);
	if ((cmd = (t_exe*)ft_memalloc(sizeof(t_exe))) == NULL)
		return (EXIT_FAILURE);
	if ((cmd->av = (char**)ft_memalloc(sizeof(char*) * 2)) == NULL)
		return (EXIT_FAILURE);
	cmd->av[0] = ft_strdup("setenv");
	cmd->av[1] = ft_strnew(7 + ft_strlen(pwd));
	cmd->av[1] = ft_strcpy(cmd->av[1], "OLDPWD=");
	cmd->av[1] = ft_strcat(cmd->av[1], pwd);
	cmd->ac = 2;
	ft_setenv(cmd);
	ft_strlst_del(&cmd->av, 2);
	free(cmd);
	return (EXIT_SUCCESS);
}
