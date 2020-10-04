/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   auto_completion.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihwang <ihwang@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/23 21:14:14 by marvin            #+#    #+#             */
/*   Updated: 2020/10/04 23:50:50 by ihwang           ###   ########.fr       */
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
# include "get_prompt.h"

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
void        set_status_root(long *status);
void        delete_status_new_pos(long *status);
void        delete_status_dir(long *status);
void        delete_status_completed(long *status);

void        auto_command(t_l *l);
void        auto_file(t_l *l);
void        auto_open_path(t_l *l);
void        auto_other_possibility(t_l *l);
void        auto_no_other_possibility(t_l *l);
void        auto_dir(t_l *l);
void		auto_print_list(t_l *l);

char        *auto_get_typed_str(t_l *l);
char        *auto_get_target_str(t_auto *auto_com);
char        auto_is_dir(char *path, char *filename);
void		auto_get_list(t_auto *auto_com, DIR *dirp);
void        auto_reset(t_auto *auto_com);
void		auto_lstdel_strdel(t_list **alst);
void        auto_reset(t_auto *auto_com);

#endif