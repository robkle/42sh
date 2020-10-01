/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthan <dthan@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/05 05:54:54 by tango             #+#    #+#             */
/*   Updated: 2020/10/01 06:05:09 by dthan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHELL_H
# define SHELL_H
# include "libft.h"
# include "../ft_printf/includes/ft_printf.h"
# include <limits.h>
# include <unistd.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <sys/signal.h>
# include <sys/ioctl.h>
# include <dirent.h>
# include <fcntl.h>
# include <term.h>
# include <termios.h>

# include "shell_error.h"
# include "ast.h"
# include "token.h"
# include "utilities.h"
# include "line_edition.h"
# include "jobs.h"

# define READ_END 0
# define WRITE_END 1

# define PARENT 1
# define CHILD 0
# define F_TYPE_MASK 0170000
# define KEY 1
# define VAL 0

typedef	struct			s_heredoc
{
	char				*heredoc;
	struct s_heredoc	*next;
}						t_heredoc;

typedef	struct			s_redirect
{
	char				*redirect_op;
	char				*redirect_src;
	char				*redirect_des;
	// struct s_redirect	*next;
}						t_redirect;

typedef struct			s_exe
{
	int					ac;
	char				**av;
	t_redirect			*redi;
	t_heredoc			*heredoc;
}						t_exe;

char					**g_env;
int						g_status;

typedef	struct stat		t_stat;
typedef	struct dirent	t_dir;

/*
**	Lexer
*/

t_token					*lexical_analysis(char *input);

/*
**	Parser
*/

t_astnode				*syntax_analysis(t_token *token);

/*
** Utilities
*/

char					*get_env(char *name, int keyval);
int						ft_isspace(int c);
char					*ft_strndup(char *str, size_t len);
void					ft_arraydel(char **string_array);
// char					*is_in_path(t_exe *c);
// int						make_child_path(t_exe *c, char *path);
// void					make_child_binary(t_exe *c);
// int						possible_to_access_dir(t_exe *c);
// int						possible_to_access_file(t_exe *c);

char					*is_in_path(t_process *c);
int						make_child_path(t_process *c, char *path);
void					make_child_binary(t_process *c);
int						possible_to_access_dir(t_process *c);
int						possible_to_access_file(t_process *c);

/*
** Prompt
*/

void					get_prompt(void);

/*
** Commands
*/

// int						ft_env(void);
// int						ft_pwd(void);
// int						ft_echo(t_exe *c);
// int						ft_exit(int opt);
// int						ft_cd(t_exe *c);
// int						ft_cd_pathfinder(t_exe *c);
// int						ft_setenv(t_exe *c);
// int						ft_unsetenv(t_exe *c);
// void					ft_type(t_exe *c);

int						ft_env(void);
int						ft_pwd(void);
int						ft_echo(t_process *c);
int						ft_exit(int opt);
int						ft_cd(t_process *c);
int						ft_cd_pathfinder(t_process *c);
int						ft_setenv(t_process *c);
int						ft_unsetenv(t_process *c);
void					ft_type(t_process *c);

/*
** Signal
*/

void					sig_controller(int option);
void					post_signal(t_l *l);
int						iseof_in_line(char *line);
void					eof_handler(t_l *l);

/*
** Executor
*/

void					executor(t_astnode *ast);

// void					execute_complete_command(t_astnode *ast, t_exe *exe);
// void					execute_list(t_astnode *ast, t_exe *exe);
// void					execute_and_or(t_astnode *ast, t_exe *exe);
// int						execute_pipeline(t_astnode *ast, t_exe *exe);
// int						execute_pipe_sequence(t_astnode *ast, t_exe *exec, t_job *job);
// int						execute_command(t_astnode *ast, t_exe *exe);
// int						execute_simple_command(t_astnode *ast, t_exe *exe);

void					execute_complete_command(t_astnode *ast, t_list **heredoc);
void					execute_list(t_astnode *ast, t_list **heredoc, t_job *fist_job);
void					execute_and_or(t_astnode *ast, t_list **heredoc, t_job *job);
int						execute_pipeline(t_astnode *ast, t_list **heredoc, t_job *job);
int						execute_pipe_sequence(t_astnode *ast, t_list **heredoc, t_job *job);
int						execute_command(t_astnode *ast, t_list **heredoc, t_job *job);
int						execute_simple_command(t_astnode *ast, t_list **heredoc, t_job *job);
void	execute_cmd_name(t_astnode *ast, t_job *j, t_process *p);
void	execute_cmd_suffix(t_astnode *ast, t_list **hd, t_job *j, t_process *p);
void	execute_io_redirect(t_astnode *ast, t_list **hd, t_process *p);


/*
** Redirect
*/

// void					handle_redirect(t_exe exe);
// void					redirect_great(t_redirect *trav);
// void					redirect_dgreat(t_redirect *trav);
// void					redirect_greatand(t_redirect *trav);
// void					redirect_lessand(t_redirect *trav);
// void					redirect_less(t_redirect *trav);
// void					redirect_dless(t_exe *exe);

void			handle_redirect(t_list *list, t_process *p);
void			redirect_great(t_redirect *trav, t_process *p);
void			redirect_dgreat(t_redirect *trav, t_process *p);
void			redirect_greatand(t_redirect *trav, t_process *p);
void		redirect_lessand(t_redirect *trav, t_process *p);
void		redirect_less(t_redirect *trav, t_process *p);
void		redirect_dless(t_redirect *trav, t_process *p);

/*
** Executor tool
*/

// void					find_heredoc(t_astnode *ast, t_exe *exe);
// // int						run(t_exe *exec);
// int						run(t_exe *exec, t_job *job);
// void					get_av_cmd_name(t_astnode *ast, t_exe *exe);
// void					get_av_cmd_suffix(t_astnode *ast, t_exe *exe, int opt);

// void					clear_exe(t_exe *exe);
void					clear_token(t_token *token);

void				find_heredoc(t_astnode *ast, t_list **heredoc);
void	clear_heredoc(t_list *heredoc);
int				lauch_process(t_job *j, t_process *p);
void lauch_child_process(t_job *j, t_process *p);

#endif
