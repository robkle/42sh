/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jobs.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthan <dthan@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/17 20:34:20 by marvin            #+#    #+#             */
/*   Updated: 2020/10/04 00:10:08 by dthan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <termios.h>
#include <sys/ioctl.h>

#include "libft.h"

typedef struct			s_process
{
	int					ac;
    char                **av;
    pid_t               pid;
	int					stdin;
	int					stdout;
	int					stderr;
	t_list				*redi;
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
	int					stdin;
	int					stdout;
	int					stderr;
	int					foreground;
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
t_list		*create_job();
void put_to_list_job(t_list *newjob);
void delete_job(t_list *j);

/* foreground and background*/
void put_job_in_foreground(t_job *job, int cont);
void put_job_in_background(t_job *job, int cont);

/* stopeed and terminated jobs*/
int mark_process_status(pid_t pid, int status);
void update_status(void);
void wait_for_job(t_job *j);
void format_job_info(t_list *j, const char *status);
void	do_job_notification(void);

/* continuing stopped jobs */
void mark_job_as_running(t_job *j);
void continue_job(t_job *j, int foreground);

int ft_jobs(void);
