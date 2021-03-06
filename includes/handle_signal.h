/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_signal.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthan <dthan@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/18 20:29:42 by marvin            #+#    #+#             */
/*   Updated: 2020/12/27 18:14:08 by dthan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HANDLE_SIGNAL_H
# define HANDLE_SIGNAL_H
# include "struct.h"

void					sig_controller(int option);
void					default_post_sigint(t_l *l);
char					*dquote_post_sigint(t_l *l);
void					post_sigwinch(t_l *l);
int						iseof_in_line(char *line);
void					eof_handler(t_l *l);

#endif
