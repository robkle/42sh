/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd_get_curpath_from_dir.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihwang <ihwang@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/02 17:35:42 by ihwang            #+#    #+#             */
/*   Updated: 2021/02/02 17:38:10 by ihwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

/*
**	step6 in posix doc
*/

char		ft_cd_get_curpath_from_dir(t_cd *cd)
{
	cd->curpath = ft_strdup(cd->directory);
	return (ft_cd_append_slash_to_curpath(cd));
}