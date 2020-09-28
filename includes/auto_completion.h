/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   auto_completion.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihwang <ihwang@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/23 21:14:14 by marvin            #+#    #+#             */
/*   Updated: 2020/09/29 00:08:26 by ihwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AUTO_COMPLETION_H
# define AUTO_COMPLETION_H

# include <unistd.h>
# include <dirent.h>
# include <sys/stat.h>
# include "libft.h"
# include "line_edition_structure.h"
# include "copy_paste.h"

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
    AUTO_STAT_OPEN = (1 << 2), // o
    AUTO_STAT_WORD_IN_PATH = (1 << 3), // o
    AUTO_STAT_OTHER_POSSIBILITY = (1 << 4),
    AUTO_STAT_COMPLETED = (1 << 5),
    AUTO_STAT_DIR = (1 << 6),
    AUTO_STAT_TYPED_UPTO = (1 << 7),
    AUTO_STAT_LIST = (1 << 8),
    AUTO_STAT_PERM = (1 << 9),
}   t_auto_com_stat;

typedef struct dirent   t_dirent;
typedef struct stat     t_stat;

void        set_status_new_pos(long *status);
void        set_status_open(long *status);
void        set_status_word_in_path(long *status);
void        set_status_other_possibility(long *status);
void        set_status_completed(long *status);
void        set_status_dir(long *status);
void        set_status_typed_upto(long *status);
void        set_status_list(long *status);
void        set_status_perm(long *status);
void        delete_status_new_pos(long *status);
void        delete_status_dir(long *status);
void        auto_command(t_l *l);
void        auto_file(t_l *l);
void        auto_open_path(t_l *l);
void        auto_no_other_possibility(t_l *l);
void        auto_dir(t_l *l);
void        auto_ready_to_print(t_l *l);
void		auto_print_list(t_l *l);
void		auto_make_list(t_auto *auto_com);

char        auto_is_dir(char *path, char *filename);
void		auto_get_list(t_auto *auto_com, DIR *dirp);
char        *auto_get_word(t_l *l);

#endif