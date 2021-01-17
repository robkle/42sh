/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthan <dthan@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/26 11:18:23 by dthan             #+#    #+#             */
/*   Updated: 2020/12/26 20:43:10 by dthan            ###   ########.fr       */
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
}	t_astnode_type;

typedef struct			s_astnode
{
	int					type;
	int					exitcode; // what is this?
	char				*data;
	struct s_astnode	*left;
	struct s_astnode	*right;
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
	AUTO_STAT_NEW_POS = (1 << 0), // o
	//AUTO_STAT_COMMAND = (1 << 1),
	//AUTO_STAT_ROOT = (1 << 10),
	//AUTO_STAT_OPEN = (1 << 2), // o
	//AUTO_STAT_WORD_IN_PATH = (1 << 3), // o
	//AUTO_STAT_OTHER_POSSIBILITY = (1 << 4),
	AUTO_STAT_COMPLETED = (1 << 5),
	AUTO_STAT_DIR = (1 << 6),
	//AUTO_STAT_TYPED_UPTO = (1 << 7),
	AUTO_STAT_LIST = (1 << 8),
	AUTO_STAT_OVER_TERM_SIZE = (1 << 9)
}   t_auto_com_stat;

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

typedef struct dirent   t_dirent;
typedef struct stat     t_stat;

/*
** Line Edit struct
*/

typedef enum
{
	CLIP_SAVE,
	CLIP_TAKE,
	CLIP_DELT,
}	t_clipping_options;


typedef struct			s_l
{
	char				*line;
	int					co;
	int					starting_row;
	int					total_row;
	int					nb;
	int					x;
	int					y;
	int					down;
	int					pmpt;
	int					type;
	int					eof_flag;
	char				*rev_sr;
	int					rs;
	int					rs_i;
	t_auto				auto_com;
}						t_l;

typedef struct termios	t_term;

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
** Alias struct
*/

typedef struct			s_alias
{
	char *value;
	char *name;
}						t_alias;

/*
** Hash struct
*/

typedef struct			s_hash
{
	char *name;
	char *path;
	int hits;
	struct s_hash	*next;
	struct s_hash	*prev;
}						t_hash;

#endif
