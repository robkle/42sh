/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_oldpwd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthan <dthan@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/02 16:11:35 by tango             #+#    #+#             */
/*   Updated: 2020/09/30 05:18:38 by dthan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

//need to check this again

int			set_oldpwd(char pwd[PATH_MAX])
{
	t_process	*cmd;

	if ((getcwd(pwd, PATH_MAX)) == NULL)
		return (EXIT_FAILURE);
	if ((cmd = (t_process*)ft_memalloc(sizeof(t_process))) == NULL)
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
