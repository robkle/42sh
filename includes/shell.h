/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthan <dthan@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/05 05:54:54 by tango             #+#    #+#             */
/*   Updated: 2020/10/07 00:13:46 by dthan            ###   ########.fr       */
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

# include <signal.h>
#define _POSIX_SOURCE


# include "shell_error.h"
# include "ast.h"
# include "token.h"
# include "utilities.h"
# include "line_edition.h"
# include "execution.h"
# include "builtin.h"

# define READ_END 0
# define WRITE_END 1

# define PARENT 1
# define CHILD 0
# define F_TYPE_MASK 0170000
# define KEY 1
# define VAL 0

typedef struct          s_shell
{
    pid_t               shell_pgid;
    struct termios      shell_tmode;
    t_list              *first_job;
	int					previous_exitcode;
}                       t_shell;

t_shell     g_shell;

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
