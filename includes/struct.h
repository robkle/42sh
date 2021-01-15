/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthan <dthan@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/26 11:18:23 by dthan             #+#    #+#             */
/*   Updated: 2021/01/12 20:11:31 by dthan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H
# include <sys/types.h>
# include <termios.h>
# include "libft.h"

/*
** ============================== CORE STRUCT =================================
*/

typedef enum
{
	TOKEN_APS, // &		control op
	TOKEN_SEMI, // ;	control op
	TOKEN_PIPE, // |	control	op
	TOKEN_OB, // (  // not support
	TOKEN_CB, // )   //not support
	TOKEN_WORD,
	TOKEN_ASSIGNMENT_WORD, //not support
	TOKEN_NAME, // not support
	TOKEN_NEWLINE, // not yet, it depends
	TOKEN_IO_NUMBER,
	TOKEN_AND_IF, // &&		control op
	TOKEN_OR_IF, // ||		control op
	TOKEN_DSEMI, // ;;  // not support
	TOKEN_GREAT, // >						reidrect op
	TOKEN_DGREAT, // >>						redirect op
	TOKEN_LESS, // <						redirect op
	TOKEN_DLESS, // <<						redirect op
	TOKEN_LESSAND, // <&					redirect op
	TOKEN_GREATAND, // >&					redirect op
	TOKEN_LESSGREAT, // <>  // not support
	TOKEN_DLESSDASH, // <<- // not support
	TOKEN_CLOBBER, // >|  // not support
	TOKEN_EOF, //eof only
	TOKEN_BROKEN, // a string with quote contain eof, and quote is not closed
}	t_token_type;

typedef struct			s_token
{
	char				*data;
	t_token_type		type;
	struct s_token		*next;
}						t_token;

typedef enum
{
	AST_complete_command = 1,
	AST_list,
	AST_and_or,
	AST_pipeline,
	AST_pipe_sequence,
	AST_command,
	AST_simple_command,
	AST_cmd_name,
	AST_cmd_prefix,
	AST_cmd_suffix,
	AST_io_redirect,
	AST_io_file,
	AST_io_here,
	AST_filename,
	AST_WORD,
	AST_ASSIGNMENT_WORD,
}	t_astnode_type;

typedef struct			s_astnode
{
	int					type;
	char				*data;
	struct s_astnode	*left;
	struct s_astnode	*right;
	struct s_astnode	*middle;
}						t_astnode;

/*
**============================= FEATURE STRUCT ================================
*/

/*
** Job, process, redi, heredoc struct
*/

typedef struct			s_heredoc
{
	char				*doc;
	struct s_heredoc	*next;
}						t_heredoc;

typedef	struct			s_redi
{
	char				*op;
	char				*n;
	char				*word;
	struct s_redi		*next;
}						t_redi;

typedef struct			s_process
{
	int					ac;
	char				**av;
	pid_t				pid;
	int					stdin;
	int					stdout;
	int					stderr;
	t_redi				*first_redi;
	char				completed;
	char				stopped;
	int					status;
	struct s_process	*next;
}						t_process;

typedef struct          s_job
{
    char                *command;
    pid_t               pgid;
    char                notified;
    struct termios      term;
	t_process			*first_process;
	int					stdin;
	int					stdout;
	int					stderr;
	int					foreground;
	char				forked;
	int					id;
	int					pipe_fd_closer[2];
	struct s_job		*next;
}                       t_job;

typedef struct dirent   t_dirent;
typedef struct stat     t_stat;

/*
** Line Edit struct
*/

typedef enum
{
	CLIP_SAVE = 0,
	CLIP_TAKE,
	CLIP_DELT
}	t_clipping_options;

typedef enum
{
	PROMPT_CMD = 0,
	PROMPT_CMD_AND,
	PROMPT_CMD_OR,
	PROMPT_PIPE,
	PROMPT_HEREDOC,
	PROMPT_DQUOTE,
	PROMPT_QUOTE,
	PROMPT_BACKSLASH,
	PROMPR_CMDSUBST
} t_prompt;

typedef enum
{
	PHASE_CMD = 0,
	PHASE_DQUOTE,
	PHASE_QUOTE,
	PHASE_BACKSLASH,
	PHASE_CMDSUBST,
	PHASE_STOP,
	PHASE_HEREDOC // temp
}	t_phase;

typedef enum
{
	LEX_SUCCESS = 0,
	LEX_FAILURE,
	LEX_CMD,
	LEX_CMDAND,
	LEX_CMDOR,
	LEX_PIPE,
	LEX_HEREDOC,
}	t_lex_value;

/*
** Line edition struct:
** 	char 	*line		: the line
**	int		co			: number of column in a line
**	int		starting_row: total_row - current_row
**	int		total_row	: number of line on screen or page
**	int		nb			: number of char in the line
**	int		x			: x cursor position
**	int		y			: y cursor position
**	int		pmpt		: length of prompt
**	char	*rev_sr		:
**	int		rs			:
**	int		rs_i		:
**	char	phase		:
**	t_auto	auto_com	:
*/

typedef struct			s_l
{
	char				*line;
	int					nb;
	int					co;
	int					total_row;
	int					starting_row;
	int					pmpt;
	int					x;
	int					y;
	t_prompt			promp_type;
	char				phase;
	// int					down; // sanitized 
	// int					eof_flag; // sanitized
	char				*rev_sr;
	int					rs;
	int					rs_i;
	// t_auto				auto_com; // delete this later
}						t_l;

typedef struct termios	t_term;

/*
** Auto completion
*/

typedef enum
{
	AUTO_ROLE_FULFILL_ALL,
	AUTO_ROLE_FULFILL_UPTO,
	AUTO_ROLE_PRINT,
	AUTO_ROLE_OPEN_LIST,
	AUTO_ROLE_ERR
}	t_auto_com_role;

typedef enum
{
	AUTO_STAT_NEW_POS = (1 << 0),
	AUTO_STAT_COMPLETED = (1 << 1),
	AUTO_STAT_DIR = (1 << 2),
	AUTO_STAT_LIST = (1 << 3),
	AUTO_STAT_OVER_TERM_SIZE = (1 << 4)
}   t_auto_com_stat;

/*
** struct auto
**	t_list			*list					: list of the options
**	size_t			largest_content_size	:
**	void			*largest_content		:
**	size_t			count_list				: number of item in list
**	char			cwd[]					: current working dir
**	char			full_path[]				:
**	char			*typed_str				:
**	char			*target_str				:
**	char			*path_env				:
**	long			status					:
*/


typedef struct			s_auto
{
    t_list              *list;
	size_t				largest_content_size;
	void				*largest_content;
	size_t				count_list;
	char				cwd[PATH_MAX];
    char                full_path[PATH_MAX];
	char				*typed_str;
    char                *target_str;
	char				*path_env;
	long				status;
	t_l					*editor;
}						t_auto;

typedef struct			s_auto_grid
{
	size_t				longest_col_len;
	size_t				term_col_len;
	size_t				col_count;
	size_t				file_count;
	size_t			    start_row;
	size_t			    end_row;
	size_t			    filled_col_count;
}						t_auto_grid;


/*
**  History struct
**		char **hist	: history of commands
**		int  hst	: keep track of the position in the array while navigating
**					  throught the history with the up and down keys
**		int  curr	: the index position after the most recent history event
**					: and always contain null characters
**		int  size   : to keep track the growing max size
*/

typedef struct	s_history
{
	char		**hist;
	char		*tmp;
	int			hst;
	int			curr;
	int			hstsize;
	char		savedfile[256];
}				t_history;

/*
** struct for options in builtin
*/



// typedef struct		s_builtin_options
// {
// 	char			*opt_set;
// 	char			set_len;
// 	unsigned int	operand_count;
// 	unsigned long	applied;
// 	char			invalid_opt;
// }					t_opt;



typedef struct s_var
{
	char *name;
	char *value;
	char exported;
} t_var;

typedef struct		s_builtin_options
{
	char			*opt_set;
	// char			set_len; // non need
	// unsigned int	operand_count;
	// unsigned long	applied;
	int				opt;
}					t_opt;

#define BUILTIN_EXPORT_OPT_SET "p"
#define EXPORT_OPT_P 1

typedef	struct			s_export
{
	char			*opt_set;
	int				opt;
	char			synopsis;
	char			*av[4096];
}					t_export;

/*
** Alias struct
*/

typedef struct			s_alias
{
	char *value;
	char *name;
}						t_alias;

#endif
