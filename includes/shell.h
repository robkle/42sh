/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthan <dthan@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/05 05:54:54 by tango             #+#    #+#             */
/*   Updated: 2021/01/05 15:49:36 by dthan            ###   ########.fr       */
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
# include <sys/signal.h>
# include <signal.h>
# include <sys/ioctl.h>
# include <dirent.h>
# include <fcntl.h>
# include <term.h>
# include <termios.h>

//#define _POSIX_SOURCE
# include <stdio.h> // for perror, need to be delete when replacing the error management

# include "struct.h"
# include "ast.h"
# include "token.h"
# include "utilities.h"
# include "line_edition.h"
# include "execution.h"
# include "builtin.h"
# include "constant.h"
# include "expansion.h"
# include "history.h"
# include "auto_completion.h"
# include "handle_signal.h"
# include "inhibitor.h"

# define F_TYPE_MASK 0170000
# define KEY 1
# define VAL 0
# define TRUE 1
# define FALSE 0

typedef struct			s_shell
{
	char				**env;
	char				**var;
	char				signal_indicator;
	char				shell_terminal;
	char				interactive_shell;
    pid_t               shell_pgid;
    struct termios      shell_tmode;
	t_job				*first_job;
	t_heredoc			*first_heredoc;
	t_history			*history;
	t_alias				**alias;
	char				*last_alias;
}                       t_shell;

t_shell     g_shell;


/*
**	Lexer
*/

// t_token					*lexer_and_parser(char *input);
t_lex_value lexical_analysis_and_syntax_analysis(char *cmd, t_token **tk_lst);

/*
**	Parser
*/

int			syntax_analysis(t_token *curr, t_token *prev);
// t_astnode				*syntax_analysis(t_token *token);

/*
** Semantic
*/

t_astnode				*semantic_analysis(t_token *token);

/*
** Prompt
*/

size_t					get_prompt(void);

/*
** Executor
*/

void					executor(t_astnode *ast);


// new
void	print_info(void);
int		print_phase(t_phase phase);

#endif
