/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthan <dthan@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/05 03:23:45 by dthan             #+#    #+#             */
/*   Updated: 2020/10/05 16:32:01 by dthan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H
# include "execution.h"

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
int		ft_jobs(void);
int		ft_fg(void);
int		ft_fc(t_process *p);
int		ft_fc_list(int flags, char **range);
int		ft_fc_range(char *str);


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
int		ft_num_check(char *str); //Temporarily here until function moved somewhere ele

#endif
