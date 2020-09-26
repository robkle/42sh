/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jobs.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthan <dthan@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/17 20:34:20 by marvin            #+#    #+#             */
/*   Updated: 2020/09/26 02:47:50 by dthan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <termios.h>
#include <sys/ioctl.h>

#include "libft.h"

typedef struct			s_process
{
    char                **argv;
    pid_t               pid;
    char                completed;
    char                stopped;
    int                 status;
}                       t_process;

typedef struct          s_job
{
    char                *command;
    pid_t               pgid;
    char                notified;
    struct termios      term;
    t_list              *process;
	int					background;
    // int                 stdin;
    // int                 stdout;
    // int                 stderr;
}                       t_job;

typedef struct          s_shell
{
    pid_t               shell_pgid;
    struct termios      shell_tmode;
    t_list              *job;
}                       t_shell;

t_shell     g_shell;

int         ft_tcsetpgrp(int fd, pid_t pgrp_id);
pid_t       ft_tcgetpgrp(int fd);