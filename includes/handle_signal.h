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

#ifndef SIGNAL_INDICATOR_H
# define SIGNAL_INDICATOR_H
# include "struct.h"

void					sig_controller(int option);
void					post_sigint(t_l *l);
void					post_sigwinch(t_l *l);
int						iseof_in_line(char *line);
void					eof_handler(t_l *l);

#endif
