/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inhibitor.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthan <dthan@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/30 19:22:41 by dthan             #+#    #+#             */
/*   Updated: 2021/01/25 07:38:06 by dthan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INHIBITOR_H
# define INHIBITOR_H

int is_quoting_phase(t_phase cur_phase);
int is_real_character(char *str, int i);
char *delete_line_feed_at_the_end_of_the_cmd_string(char *cmd);

#endif
