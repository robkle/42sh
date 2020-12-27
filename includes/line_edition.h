/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_edition.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthan <dthan@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/16 21:44:40 by ihwang            #+#    #+#             */
/*   Updated: 2020/12/27 17:09:19 by dthan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LINE_EDITION_H
# define LINE_EDITION_H
# include "struct.h"

# define LEFT "#4"

# define BUFF_LINE_EDITION 8
# define LINE_TYPE_SINGLE 0
# define LINE_TYPE_DQUOTE 1
# define LINE_TYPE_HEREDOC 2

# define ERR_EOF 1

# define INIT "\033[0m"
# define BOLD "\033[1m"
# define RED "\033[31m"
# define GREN "\033[32m"
# define YELW "\033[33m"
# define BLUE "\033[34m"
# define MGTA "\033[35m"
# define CYAN "\033[36m"
# define GRSS "\033[92m"
# define TMGT "\033[95m"
# define SKYB "\033[96m"


void	ft_get_line(t_l *l);

/*
** Available keys
*/

void	up_down(t_l *l, char t[]);
void	right_key(t_l *l);
void	left_key(t_l *l);
int		bs_key(t_l *l);
void	add_key(char t[], t_l *l);
int		home_key(t_l *l);
int		end_key(t_l *l);
int		ctrl_k(t_l *l, int y_dec);
int		ctrl_l(t_l *l, int clip_len, int i);
void	ctrl_left(t_l *l, int y_dec);
void	ctrl_right(t_l *l);
void	ctrl_up(t_l *l);
void	ctrl_down(t_l *l);
void	carriage_return_key(t_l *l);
int						auto_complete(t_l *l);

/*
** Term_attr
*/

void	init_term(t_l *l);
t_term	get_set_default_term(t_term *t);
void	restore_term(t_l *l);
void	get_new_term_cursor(t_l *l);


/*
** add key
*/

void				add_key(char t[], t_l *l);

/*
** Copy & Paste
*/

int		cutting(t_l *l, int y_dec);
void	cutting_clipping(t_l *l, int i, int j);
char	*clipboard(char *str, int opt);
int		paste(t_l *l, char raw_clip[], int clip_len, \
                        char *autocom_clip);
void	paste_background(t_l *l, int clip_len);
char	*get_clip_external(char raw_clip[]);
char	*get_clip_autocom(t_auto *auto_com);

/*
** Line Edition Utilities
*/

void					apply_termcap_str(char *str, int x, int y);
size_t					get_current_row(void);
size_t					get_current_column(void);
int		ft_count_rows(t_l *l);
#endif
