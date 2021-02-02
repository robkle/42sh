/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intern_and_environment_var.h                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthan <dthan@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/15 09:19:45 by dthan             #+#    #+#             */
/*   Updated: 2021/01/27 12:52:07 by dthan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INTERN_AND_ENVIRONMENT_VAR_H
# define INTERN_AND_ENVIRONMENT_VAR_H
# include "struct.h"

/*
** ========================= Environment variable =============================
** format:
** NAME=VALUE
** name and value is true value, no null
*/

char	*ft_getenv(const char *name);
void	add_environment_var(char *name, char *value);
void	update_environment_var(char *name, char *value);
void	add_update_environment_var(char *name, char *value);
int		is_eligible_to_export_to_env(t_var var);
char	**set_env(char **sample);
void	delete_environment_var(char *name);

/*
** =========================== Internal variable ==============================
** format:
** name, value, export
** value can be null
** NOTE:
** + is_intern_var and ft_get_var should use together
** 		is_intern_var check if there is intern var's name in the table
**			value could be Null or valid
** 		ft_getvar return the value of intern var's name and NULL if
**			there is no intern var in the table or the intern var has no value
*/

int		is_intern_var(char *name);
t_var	*ft_getvar(char *name);
void	add_intern_var(t_var *new_var);
void	update_intern_var(t_var *intern_var);
t_var	**set_var(char **envp);
int		count_intern_var_table(t_var **table);
void	clean_table_intern_var(t_var **table);
void	clear_intern_var(t_var *intern_var);
void	delete_intern_var(char *name);

#endif
