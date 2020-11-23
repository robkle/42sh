/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthan <dthan@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/17 20:34:20 by marvin            #+#    #+#             */
/*   Updated: 2020/10/29 06:13:02 by dthan            ###   ########.fr       */
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
# define COMPLETED_JOB 1
# define SUSPENDED_JOB 2

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
	char				forked;
	int					id;
}                       t_job;

typedef	struct			s_redi
{
	char				*op;
	char				*n;
	char				*word;
}						t_redi;

/*
** ========================== EXECUTION FUNCTIONS =============================
*/

void	execute_complete_command(t_astnode *ast);
void	execute_list(t_astnode *ast, int foreground);
void	execute_and_or(t_astnode *ast, int foreground, int forked, int noticed);
void	execute_and_or_bg(t_astnode *ast);
void	execute_pipeline(t_astnode *ast, t_job *job);
void	execute_pipe_sequence(t_astnode *ast, t_job *job);
void	execute_command(t_astnode *ast, t_job *job);
void	execute_simple_command(t_astnode *ast, t_job *job);
void	execute_cmd_name(t_astnode *ast, t_job *j, t_process *p);
void	execute_cmd_suffix(t_astnode *ast, t_job *j, t_process *p);
void	execute_io_redirect(t_astnode *ast,t_process *p);
void	find_heredoc(t_astnode *ast);
void	clear_heredoc(t_list *heredoc);

/*
** ========================== REDIRECTION FUNCTIONS ===========================
*/

int	handle_redirection(t_list *list, t_process *p);
int	redirect_great(t_redi *redi, t_process *p);
int	redirect_dgreat(t_redi *redi, t_process *p);
int	redirect_greatand(t_redi *redi, t_process *p);
int	redirect_lessand(t_redi *redi, t_process *p);
int	redirect_less(t_redi *redi, t_process *p);
int	redirect_dless(t_redi *redi, t_process *p);

/*
** ========================== JOB CONTROL FUNCTIONS ===========================
*/

void	lauch_simple_command(t_job *j, t_process *p);
void	put_job_in_foreground(t_job *job, int cont);
void	put_job_in_background(t_job *job, int cont);
int		mark_process_status(pid_t pid, int status);
void	update_status(void);
// void	wait_for_job(t_job *j);
void	wait_for_job(t_job *j, int opt);
void	format_job_info(t_job *j, int opt, const char *status);
void	do_job_notification(void);
void	mark_job_as_running(t_job *j);
void	continue_job(t_job *j, int foreground);
int		ft_tcsetpgrp(int fd, pid_t pgrp_id);
pid_t	ft_tcgetpgrp(int fd);

void	delete_job(t_list *j);
t_list *find_job(pid_t pgid);
int		job_is_stopped(t_job *j);
int		job_is_completed(t_job *j);
char *build_job_command(char *old_cmd, char *str);
void job_command_builder(int argc, t_job *j, ...);
void print_job_background(t_list *job_node);
int is_valid_job_id(t_job *current_j, char *str);

int is_number_str(char *str);

t_process	*create_process(t_job *j);
int last_process_status(t_job *job);
t_job	*create_job(int foreground, int forked);
t_job *find_job_with_id(int job_id);
t_job *find_the_last_job(t_job *current_j);
#endif
