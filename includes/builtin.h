/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthan <dthan@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/05 03:23:45 by dthan             #+#    #+#             */
/*   Updated: 2020/12/26 19:57:47 by dthan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H
# include "struct.h"

/*
** ========================== builtin functions ============================
*/

int		ft_env(void);
int		ft_pwd(void);
int		ft_echo(t_process *c);
int		ft_exit(int opt);
int		ft_cd(t_process *c);
int		ft_cd_pathfinder(t_process *c);
int		ft_setenv(t_process *c);
int		ft_unsetenv(t_process *c);
void	ft_type(t_process *c);
int		ft_jobs(t_process *p);
int		ft_jobs_child(t_process *p);
int		ft_fg(t_process *p);
int		ft_fg_child();
int		ft_bg(t_process *p);
int		ft_bg_child();


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
/*
** End of Fc built-in
*/

int		ft_fg_child();

/*
** Alias built-in
*/
int		ft_alias(t_process *c);
int		ft_unalias(t_process *c);
/*
** End Alias built-in
*/

int     ft_hash(t_process *c);

/*
** =============================== Utils ===================================
*/

int		is_in_path(t_process *c);
char	*build_path(t_process *c);
int		make_child_path(t_process *c);
int		make_child_binary(t_process *c);
int		possible_to_access_dir(t_process *c);
int		possible_to_access_file(t_process *c);
int		is_builtin_printing(char *comm);
void	builtins_printing(t_process *p);
int		is_builtin_not_printing(char *comm);
int		builtins_not_printing(t_process *coms);
char	*set_value(char *argv);
char	*set_name(char *argv);
void	sort_alias_list(t_alias **aliaslist);

#endif
