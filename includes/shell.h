/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthan <dthan@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/05 05:54:54 by tango             #+#    #+#             */
/*   Updated: 2020/11/01 00:52:54 by dthan            ###   ########.fr       */
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
# include <signal.h>
# include <sys/ioctl.h>
# include <dirent.h>
# include <fcntl.h>
# include <term.h>
# include <termios.h>

# include <signal.h>
//#define _POSIX_SOURCE
# include <stdio.h> // for perror, need to be delete when replacing the error management

# include "shell_error.h"
# include "ast.h"
# include "token.h"
# include "utilities.h"
# include "line_edition.h"
# include "execution.h"
# include "builtin.h"
# include "../ft_printf/includes/ft_printf.h"

# define READ_END 0
# define WRITE_END 1

# define PARENT 1
# define CHILD 0
# define F_TYPE_MASK 0170000
# define KEY 1
# define VAL 0

# define SHELL_NAME "42sh"

typedef struct			s_shell
{
	char				**env;
	char				shell_terminal;
	char				interactive_shell;
	pid_t				shell_pgid;
	struct termios		shell_tmode;
	t_list				*first_job;
	t_list				*heredoc;
}						t_shell;

t_shell					g_shell;

char					**g_env;
int						g_status;

typedef	struct stat		t_stat;
typedef	struct dirent	t_dir;

/*
**	Lexer
*/

// t_token				*lexical_analysis(char *input);
t_token					*lexer_and_parser(char *input);
/*
**	Parser
*/

t_astnode				*syntax_analysis(t_token *token);

/*
** Prompt
*/

void					get_prompt(void);

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

/*
** Executor tool
*/

#endif
