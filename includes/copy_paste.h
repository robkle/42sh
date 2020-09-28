/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   copy_paste.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihwang <ihwang@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/25 22:31:13 by marvin            #+#    #+#             */
/*   Updated: 2020/09/26 21:34:25 by ihwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PASTE_H
# define PASTE_H

# include <sys/ioctl.h>
# include <term.h>
# include "line_edition_structure.h"
# include "line_edition_utilities.h"
# include "libft.h"

# define CLIP_SAVE 0
# define CLIP_TAKE 1
# define CLIP_DELT 2

int						ctrl_k(t_l *l, int y_dec);
void					ctrl_k_clipping(t_l *l, int i, int j);
char					*clipboard(char *str, int opt);
int						paste(t_l *l, char raw_clip[], int clip_len, \
                        char *autocom_clip);
void					paste_background(t_l *l, int clip_len);
char	    			*get_clip_external(char raw_clip[]);
char	    			*get_clip_autocom(t_auto *auto_com);

#endif
