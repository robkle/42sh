/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthan <dthan@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/05 03:23:45 by dthan             #+#    #+#             */
/*   Updated: 2020/10/16 15:25:46 by dthan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H
# include "shell.h"

typedef struct			s_alias
{
	char *value;
	char *name;
}						t_alias;

t_alias					**g_alias;

char					*g_last_alias;

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
int		ft_jobs(t_job *j, t_process *p);
int		ft_fg(t_job *j, t_process *p);
int		ft_fg_child();
int		ft_bg(t_job *j, t_process *p);
int		ft_alias(t_process *c);
int		ft_unalias(t_process *c);

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
