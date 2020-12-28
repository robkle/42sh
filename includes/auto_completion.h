/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   auto_completion.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthan <dthan@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/26 20:12:39 by dthan             #+#    #+#             */
/*   Updated: 2020/12/27 17:48:04 by dthan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AUTO_COMPLETION_H
# define AUTO_COMPLETION_H
# include "libft.h"
# include "struct.h"
# include <dirent.h>
# define AUTO_COMPLETION 2

void        set_status_new_pos(long *status);
void        set_status_completed(long *status);
void        set_status_dir(long *status);
void        set_status_list(long *status);
void        set_status_over_term_size(long *status);
void        delete_status_new_pos(long *status);
void        delete_status_dir(long *status);
void        delete_status_completed(long *status);
void        delete_status_over_term_size(long *status);

void        auto_file(t_l *l);
void        auto_command(t_l *l);
void        auto_file_open_path(t_l *l);
void        auto_cmd_file_multiple_cases(t_l *l);
void        auto_file_one_case(t_l *l);
void        auto_dir(t_l *l);
void		auto_print_list(t_l *l);

void		auto_add_one_extra_char(t_l *l, char c);
void		auto_add_list_on_spot(t_auto *auto_com, t_list *node);
void        auto_complete_cmd_file(t_l *l);
char        *auto_get_typed_str(t_l *l);
char        *auto_get_target_str(t_auto *auto_com);
char        auto_is_dir(char *path, char *filename);
void		auto_get_list(t_auto *auto_com, DIR *dirp);
void        auto_reset(t_auto *auto_com);
void		auto_lstdel_strdel(t_list **alst);
void        auto_reset(t_auto *auto_com);
char        auto_is_separator(char c);

#endif
