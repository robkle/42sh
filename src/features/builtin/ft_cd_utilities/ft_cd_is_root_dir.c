/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd_is_root_dir.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihwang <ihwang@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/02 17:27:29 by ihwang            #+#    #+#             */
/*   Updated: 2021/02/02 17:27:34 by ihwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

char is_root_dir(char *path)
{
    t_stat root;
    t_stat path_stat;

    if (path == NULL)
        return (FALSE);
    stat("/", &root);
    stat(path, &path_stat);
    if (root.st_dev != path_stat.st_dev || \
        root.st_ino != path_stat.st_ino)
        return (FALSE);
    return (TRUE);
}
