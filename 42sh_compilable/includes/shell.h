/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihwang <ihwang@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/05 05:54:54 by tango             #+#    #+#             */
/*   Updated: 2020/09/15 21:53:28 by ihwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHELL_H
# define SHELL_H
# include "libft.h"
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
# include <stdbool.h>

# include "shell_error.h"
# include "ast.h"
# include "token.h"
# include "utilities.h"
# include "line_edition.h"

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
	struct s_redirect	*next;
}						t_redirect;

typedef struct			s_exe
{
	int					ac;
	char				**av;
	t_redirect			*redi;
	t_heredoc			*heredoc;
}						t_exe;

char					**g_env;
char					**g_var;
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

char					*get_var(char *name, char **lst_var, int keyval);
int						ft_isspace(int c);
char					*ft_strndup(char *str, size_t len);
void					ft_arraydel(char **string_array);
char					*is_in_path(t_exe *c);
int						make_child_path(t_exe *c, char *path);
void					make_child_binary(t_exe *c);
int						possible_to_access_file(t_exe *c);

/*
** Prompt
*/

void					get_prompt(void);

/*
** Commands
*/

int						ft_env(void);
int						ft_set(void);
int						ft_pwd(void);
int						ft_echo(t_exe *c);
int						ft_exit(int opt);
char					*ft_cd(t_exe *c);
char					*ft_cd_pathfinder(t_exe *c);
int						ft_setenv(t_exe *c);
char					*ft_unset(t_exe *c, char ***lst_var);
char					*ft_export(t_exe *c);
void					ft_type(t_exe *c);
char					*ft_set_intern_var(t_exe *c);

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

void					execute_complete_command(t_astnode *ast, t_exe *exe);
void					execute_list(t_astnode *ast, t_exe *exe);
void					execute_and_or(t_astnode *ast, t_exe *exe);
int						execute_pipeline(t_astnode *ast, t_exe *exe);
int						execute_pipe_sequence(t_astnode *ast, t_exe *exec);
int						execute_command(t_astnode *ast, t_exe *exe);
int						execute_simple_command(t_astnode *ast, t_exe *exe);

/*
** Redirect
*/

void					handle_redirect(t_exe exe);
void					redirect_great(t_redirect *trav);
void					redirect_dgreat(t_redirect *trav);
void					redirect_greatand(t_redirect *trav);
void					redirect_lessand(t_redirect *trav);
void					redirect_less(t_redirect *trav);
void					redirect_dless(t_exe *exe);

/*
** Executor tool
*/

void					find_heredoc(t_astnode *ast, t_exe *exe);
int						run(t_exe *exec);
void					get_av_cmd_name(t_astnode *ast, t_exe *exe);
void					get_av_cmd_suffix(t_astnode *ast, t_exe *exe, int opt);

void					clear_exe(t_exe *exe);
void					clear_token(t_token *token);

#endif
