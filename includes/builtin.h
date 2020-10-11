/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihwang <ihwang@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/05 03:23:45 by dthan             #+#    #+#             */
/*   Updated: 2020/10/10 18:14:21 by ihwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H
# include "execution.h"
# include "utilities.h"

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
char	*ft_unset(t_process *c, char ***lst_var);
void	ft_type(t_process *c);
int		ft_jobs(void);
int		ft_fg(void);
char	*ft_set_intern_var(t_process *c);

/*
** =============================== Utils ===================================
*/

char	*is_in_path(t_process *c);
int		make_child_path(t_process *c, char *path);
void	make_child_binary(t_process *c);
int		possible_to_access_dir(t_process *c);
int		possible_to_access_file(t_process *c);
int		is_builtin_printing(char *comm);
void	builtins_printing(t_process *p);
int		is_builtin_not_printing(char *comm);
int		builtins_not_printing(t_process *coms);

#endif
