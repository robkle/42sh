/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihwang <ihwang@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/05 05:54:54 by tango             #+#    #+#             */
/*   Updated: 2020/10/11 14:51:13 by ihwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHELL_H
# define SHELL_H
# include "libft.h"
# include "ft_printf.h"
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

# include "shell_struct.h"
# include "shell_error.h"
# include "ast.h"
# include "token.h"
# include "utilities.h"
# include "line_edition.h"
# include "execution.h"
# include "builtin.h"
# include "auto_completion.h"

# define READ_END 0
# define WRITE_END 1

# define PARENT 1
# define CHILD 0
# define F_TYPE_MASK 0170000
# define TRUE 1
# define FALSE 0

typedef enum
{
	SIGINT_INDICATOR = (1 << 0),
	SIGWINCH_INDICATOR = (1 << 1),
}	t_signal_indicator;

typedef	struct stat		t_stat;
typedef	struct dirent	t_dir;

t_shell     g_shell;

//int						g_status;

/*
**	Lexer
*/

t_token					*lexical_analysis(char *input);

/*
**	Parser
*/

t_astnode				*syntax_analysis(t_token *token);

/*
** Signal
*/

void					sig_controller(int option);
void					post_sigint(t_l *l);
void					post_sigwinch(t_l *l);
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
