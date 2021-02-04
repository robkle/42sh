/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd_append_slash_to_curpath.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihwang <ihwang@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/02 17:37:19 by ihwang            #+#    #+#             */
/*   Updated: 2021/02/02 17:47:40 by ihwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

/*
**	step7 in posix doc
*/

int ft_cd_append_slash_to_curpath(t_cd *cd)
{
	char *pwd;
	char *tmp;

	if (cd->opt.applied & BUILTIN_CD_OPT_P)
		return (ft_cd_change_dir(cd));
	if (*cd->curpath != '/')
	{
		if (((pwd = ft_getenv("PWD")) == NULL))
			return (ft_cd_prune_dotdot_dot_slash(cd));
		else if (pwd[ft_strlen(pwd) - 1] == '/')
			cd->curpath = ft_strjoin_and_free_string2(pwd, cd->curpath);
		else
		{
			tmp = ft_strjoin(pwd, "/");
			cd->curpath = ft_strjoin_and_free_2strings(tmp, cd->curpath); 
		}
	}
	return (ft_cd_prune_dotdot_dot_slash(cd));
}
