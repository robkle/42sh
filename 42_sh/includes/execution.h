/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthan <dthan@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/17 20:34:20 by marvin            #+#    #+#             */
/*   Updated: 2020/10/06 17:19:13 by dthan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H
# include <unistd.h>
# include <termios.h>
# include <sys/ioctl.h>
# include "ast.h"

/*
** =============================== DATA STRUCTURE =============================
*/

# define NOT_COMPLETED 0
# define COMPLETED 1
# define NOT_STOPPED 0
# define STOPPED 1
# define UNAVAILABLE_STATUS 0

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
    t_list              *first_process;
	int					stdin;
	int					stdout;
	int					stderr;
	int					foreground;
}                       t_job;

typedef	struct			s_redirect
{
	char				*redirect_op;
	char				*redirect_src;
	char				*redirect_des;
}						t_redirect;

/*
** ========================== EXECUTION FUNCTIONS =============================
*/

void	execute_complete_command(t_astnode *ast, t_list **heredoc);
void	execute_list(t_astnode *ast, t_list **heredoc, t_list *job);
void	execute_and_or(t_astnode *ast, t_list **heredoc, t_job *job);
void	execute_pipeline(t_astnode *ast, t_list **heredoc, t_job *job);
void	execute_pipe_sequence(t_astnode *ast, t_list **heredoc, t_job *job);
void	execute_command(t_astnode *ast, t_list **heredoc, t_job *job, t_process *p);
void	execute_simple_command(t_astnode *ast, t_list **heredoc, t_job *job, t_process *p);
void	execute_cmd_name(t_astnode *ast, t_job *j, t_process *p);
void	execute_cmd_suffix(t_astnode *ast, t_list **hd, t_job *j, t_process *p);
void	execute_io_redirect(t_astnode *ast, t_list **hd, t_process *p);

/*
** ========================== REDIRECTION FUNCTIONS ===========================
*/

void	handle_redirect(t_list *list, t_process *p);
void	redirect_great(t_redirect *trav, t_process *p);
void	redirect_dgreat(t_redirect *trav, t_process *p);
void	redirect_greatand(t_redirect *trav, t_process *p);
void	redirect_lessand(t_redirect *trav, t_process *p);
void	redirect_less(t_redirect *trav, t_process *p);
void	redirect_dless(t_redirect *trav, t_process *p);
void	find_heredoc(t_astnode *ast, t_list **heredoc);
void	clear_heredoc(t_list *heredoc);

/*
** ========================== JOB CONTROL FUNCTIONS ===========================
*/

int		lauch_process(t_job *j, t_process *p);
void	lauch_child_process(t_job *j, t_process *p);
void	put_job_in_foreground(t_job *job, int cont);
void	put_job_in_background(t_job *job, int cont);
int		mark_process_status(pid_t pid, int status);
void	update_status(void);
void	wait_for_job(t_job *j);
void	format_job_info(t_job *j, const char *status);
void	do_job_notification(void);
void	mark_job_as_running(t_job *j);
void	continue_job(t_job *j, int foreground);
int		ft_tcsetpgrp(int fd, pid_t pgrp_id);
pid_t	ft_tcgetpgrp(int fd);
t_list	*create_job();
void	put_to_list_job(t_list *newjob);
void	delete_job(t_list *j);
int		job_is_stopped(t_job *j);
int		job_is_completed(t_job *j);

#endif
