/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   auto_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihwang <ihwang@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/27 13:47:12 by marvin            #+#    #+#             */
/*   Updated: 2020/09/28 22:53:58 by ihwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "auto_completion.h"

char        *auto_get_word(t_l *l)
{
    int     tail;
    int     head;

    tail = l->x + (l->y * l->co) - l->pmpt;
    head = tail;
    while (!ft_iswhite(l->line[--head]))
        NULL;
	return (ft_strndup(&l->line[head + 1], tail - head));
	//l->auto_com->word = ft_strndup(&l->line[head + 1], tail - head);
}

void        get_path(t_l *l)
{
    char    path[PATH_MAX];
    char    *temp_word;

    temp_word = l->auto_com->word;
    // if (ft_strrchr(temp_word, '/'))
    // {
    //     if (temp_word[0] == '/')
    //         l->auto_com->path = ft_strsub(temp_word, 0, \
    //             (int)(ft_strrchr(temp_word, '/') - temp_word));
    //     // else
    //     // {
    //     //     ft_addchar(getcwd(path, PATH_MAX), '/');
    //     //     l->auto_com->path = ft_strjoin(path, temp_word);
    //     // }
    // }
	if (temp_word[0] == '/')
		l->auto_com->path = ft_strsub(temp_word, 0, \
		(int)(ft_strrchr(temp_word, '/') - temp_word));
    else
        l->auto_com->path = ft_strdup(getcwd(path, PATH_MAX));
}

// void        auto_get_path(t_l *l)
// {
//     char    path[PATH_MAX];
//     int     tail;
//     int     head;
//     char    *temp;

//    tail = l->x + (l->y * l->co) - l->pmpt;
//    head = tail;
//    while (!ft_iswhite(l->line[--head]))
//        NULL;
//    l->auto_com->word = ft_strndup(&l->line[head + 1], tail - head);
    // temp = l->auto_com->word;
    // if (ft_strrchr(temp, '/'))
    // {
    //     if (temp[0] == '/')
    //         l->auto_com->path = ft_strsub(temp, 0, \
    //             (int)(ft_strrchr(temp, '/') - temp));
    //     else
    //     {
    //         ft_addchar(getcwd(path, PATH_MAX), '/');
    //         l->auto_com->path = ft_strjoin(path, temp);
    //     }
    // }
    // else
    //     l->auto_com->path = ft_strdup(getcwd(path, PATH_MAX));
//}

char        auto_has_access(t_auto *auto_com)
{
    if (auto_com->path)
    {
        if (access(auto_com->path, F_OK))
            return (FALSE);
        else if (access(auto_com->path, X_OK))
            return (FALSE);
    }
    return (TRUE);
}

void        auto_file(t_l *l)
{
    if (l->auto_com->word)
        ft_strdel(&l->auto_com->word);
    l->auto_com->word = auto_get_word(l);
    if (!l->auto_com->path)
		get_path(l);
    if (auto_has_access(l->auto_com))
        auto_open_path(l);
    else
        NULL; // done
}
