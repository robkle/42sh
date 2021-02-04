/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihwang <ihwang@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/05 03:23:45 by dthan             #+#    #+#             */
/*   Updated: 2021/02/04 20:00:45 by ihwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H
# include "struct.h"

/*
** ========================== builtin functions ============================
*/

int		ft_env(void);
int		ft_pwd(t_process *p);
int		ft_echo(t_process *c);
int		ft_exit(t_process *p);
int		ft_cd(t_process *c);
int		ft_setenv(t_process *c);
int		ft_unsetenv(t_process *c);
int		ft_type(t_process *c);
int		ft_jobs(t_process *p);
int		ft_jobs_child(t_process *p);
int		ft_fg(t_process *p);
int		ft_fg_child();
int		ft_bg(t_process *p);
int		ft_bg_child();
int		ft_export(int ac, char **av);
int		ft_set(void);
int		ft_unset(int ac, char **av);

/*
** Exit built-in
*/

int		ft_exit_internal(int opt);

/*
** Cd built-in
*/

# define FT_CD_NULL_LEN 1

int		ft_cd_search_cdpath(t_cd *cd);
char	ft_cd_get_curpath_from_dir(t_cd *cd);
int		ft_cd_append_slash_to_curpath(t_cd *cd);
int		ft_cd_prune_dotdot_dot_slash(t_cd *cd);
int		ft_cd_compress_curpath(t_cd *cd);
int		ft_cd_change_dir(t_cd *cd);


/*
** End of Cd built-in
*/

/*
** Fc built-in
*/
# define FC_MODE_LISTING
# define FC_MODE_EDITING
# define DEFAULT_EDITOR "vim"
# define FC_EDITING_FILE "/tmp/fc_42sh"
# define FC_L_OP 1
# define FC_N_OP 2
# define FC_R_OP 4
# define FC_S_OP 8
# define FC_E_OP 16
# define FIRST 0
# define LAST 1
# define REPLACE 2

void	fc_cleanup(char *editor, char **block);
int 	fc_error_no_command_found(void);
int 	fc_error_history_specification_out_of_range(void);
int 	fc_range(char *str);
int		fc_exec(int ops, char *editor, char **block);
int		fc_s_op(char *replace, char *first);
int		fc_e_op(int ops, char *editor, char *first, char *last);
int		fc_list(int ops, char *first, char *last);
int		ft_fc(t_process *p);
void ft_fc_execute(char *cmd);
/*
** End of Fc built-in
*/

int		ft_fg_child();

/*
** Alias built-in
*/
int		ft_alias(t_process *c);
int		ft_unalias(t_process *c);
int		is_alias(char *str, t_token *prev_token);
void	alias_substitution(t_token **current_token, t_token **prev_token, t_token **tk_lst);
char	*find_alias_str(char *str);
/*
** End Alias built-in
*/

/*
** Hash built-in
*/
int     ft_hash(t_process *c);
void     add_hashentry(char *name, char *path, int hits);
unsigned int     hash_index(char *name);
void	remove_hashentries(void);
t_hash			*create_hash_node(char *name, char *path, int hits);
unsigned int	hash_index(char *name);
/*
** End Hash built-in
*/

/*
** Type built-in
*/
t_builtin	*set_builtin_commands(void);
void		delete_builtin_commands(void);
/*
** End type built-in
*/


/*
** =============================== Utils ===================================
*/

int		is_in_path(t_process *c);
char	*build_path(t_process *c);
char	*make_child_path(t_process *c);
int		make_child_binary(t_process *c);
int     make_child_path_sub(t_process *c, char buf[]);
int		possible_to_access_dir(t_process *c);
int		possible_to_access_file(t_process *c);
int		is_builtin_printing(char *comm);
void	builtins_printing(t_process *p);
int		is_builtin_not_printing(char *comm);
int		builtins_not_printing(t_process *coms);
char	*set_value(char *argv);
char	*set_name(char *argv);
void	sort_alias_list(t_alias **aliaslist);
char	*search_path(char *name, char *path);
char	*find_executable(char *name);
void	destroy_arr(char **arr);
void	ft_cd_pwd_check_builtin_opts(char **av, t_opt *opt);
void    ft_cd_pwd_init_opt(t_opt *opt, const char *opt_set);
char	is_root_dir(char *path);

#endif
