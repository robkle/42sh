/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_struct.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihwang <ihwang@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/11 14:49:22 by marvin            #+#    #+#             */
/*   Updated: 2020/10/11 14:50:50 by ihwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHELL_STRUCT_H
# define SHELL_STRUCT_H

# include "libft.h"
# include <termios.h>

typedef struct          s_shell
{
    pid_t               shell_pgid;
    struct termios      shell_tmode;
    t_list              *first_job;
	int					previous_exitcode;
    long                signal_indicator;
    char                **env;
    char                **var;
}                       t_shell;

#endif
