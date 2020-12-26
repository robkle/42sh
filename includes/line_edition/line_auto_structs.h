/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_auto_structs.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihwang <ihwang@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/25 22:32:11 by marvin            #+#    #+#             */
/*   Updated: 2020/12/26 09:10:40 by ihwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LINE_AUTO_STRUCTS_H
# define LINE_AUTO_STRUCTS_H

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
	//AUTO_STAT_COMMAND = (1 << 1),
	//AUTO_STAT_ROOT = (1 << 10),
	//AUTO_STAT_OPEN = (1 << 2), // o
	//AUTO_STAT_WORD_IN_PATH = (1 << 3), // o
	//AUTO_STAT_OTHER_POSSIBILITY = (1 << 4),
	AUTO_STAT_COMPLETED = (1 << 5),
	AUTO_STAT_DIR = (1 << 6),
	//AUTO_STAT_TYPED_UPTO = (1 << 7),
	AUTO_STAT_LIST = (1 << 8),
	AUTO_STAT_OVER_TERM_SIZE = (1 << 9)
}   t_auto_com_stat;

typedef struct			s_auto
{
    t_list              *list;
	size_t				largest_content_size;
	void				*largest_content;
	size_t				count_list;
	char				cwd[PATH_MAX];
    char                full_path[PATH_MAX];
	char				*typed_str;
    char                *target_str;
	char				*path_env;
	long				status;
}						t_auto;

typedef struct			s_auto_grid
{
	size_t				longest_col_len;
	size_t				term_col_len;
	size_t				col_count;
	size_t				file_count;
	size_t			    start_row;
	size_t			    end_row;
	size_t			    filled_col_count;
}						t_auto_grid;

typedef struct			s_l
{
	char				*line;
	int					co;
	int					starting_row;
	int					total_row;
	int					nb;
	int					x;
	int					y;
	int					curr;
	int					pmpt;
	int					type;
	int					eof_flag;
	t_auto				auto_com;
}						t_l;

#endif