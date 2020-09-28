/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_edition_structure.h                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihwang <ihwang@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/25 22:32:11 by marvin            #+#    #+#             */
/*   Updated: 2020/09/28 14:17:52 by ihwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LINE_EDITION_STRUCTURE_H
# define LINE_EDITION_STRUCTURE_H

# include <dirent.h>
# include "libft.h"

# define BUFF_LINE_EDITION 8

typedef struct			s_auto
{
    t_list              *list;
	long				count_list;
    char                *path;
    char                *word; //Not freed yet
//    DIR                 *dirp; //Not freed yet
	long				status;
}						t_auto;

typedef struct			s_l
{
	char				*line;
	int					co;
	int					starting_row;
	int					total_row;
	int					nb;
	int					x;
	int					y;
	int					down;
	int					curr;
	int					pmpt;
	int					type;
	int					eof_flag;
	t_auto				*auto_com; //need to be initialized
}						t_l;

#endif