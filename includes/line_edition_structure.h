/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_edition_structure.h                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihwang <ihwang@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/25 22:32:11 by marvin            #+#    #+#             */
/*   Updated: 2020/10/01 00:16:54 by ihwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LINE_EDITION_STRUCTURE_H
# define LINE_EDITION_STRUCTURE_H

# include <dirent.h>
# include "libft.h"

# define BUFF_LINE_EDITION 8
# define AUTO_COMPLETION 2
# define TRUE 1
# define FALSE 0

typedef enum
{
	AUTO_ROLE_FULFILL_ALL,
	AUTO_ROLE_FULFILL_UPTO,
	AUTO_ROLE_PRINT,
	AUTO_ROLE_OPEN_LIST,
	AUTO_ROLE_ERR
}	t_auto_com_role;

typedef enum
{
	AUTO_STAT_NEW_POS = (1 << 0), // o
	AUTO_STAT_COMMAND = (1 << 1),
	AUTO_STAT_ROOT = (1 << 10),
	AUTO_STAT_OPEN = (1 << 2), // o
	AUTO_STAT_WORD_IN_PATH = (1 << 3), // o
	AUTO_STAT_OTHER_POSSIBILITY = (1 << 4),
	AUTO_STAT_COMPLETED = (1 << 5),
	AUTO_STAT_DIR = (1 << 6),
	AUTO_STAT_TYPED_UPTO = (1 << 7),
	AUTO_STAT_LIST = (1 << 8),
	AUTO_STAT_PERM = (1 << 9),
}   t_auto_com_stat;

typedef struct			s_auto
{
    t_list              *list;
	size_t				largest_list_size;
	size_t				count_list;
	char				cwd[PATH_MAX];
    char                full_path[PATH_MAX];
	char				*typed_str;
    char                *target_str; //Not freed yet
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