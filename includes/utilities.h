/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilities.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihwang <ihwang@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/13 11:35:45 by dthan             #+#    #+#             */
/*   Updated: 2020/10/04 23:50:23 by ihwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILITIES_H
# define UTILITIES_H

# include <stdlib.h>
# include "libft.h"

# define KEY 1
# define VAL 0

char	**g_env;

char	**add_env(char *arg, char **env_list);
int		is_open_dquote(char *input, int level, char *quote);
int		is_made_of_digits(char *data);
int		input_contain_dquote(char *input);
char	*ft_strjoin_and_free_string2(char *string1, char *string2);
char	*ft_strjoin_and_free_string1(char *string1, char *string2);
int 	set_oldpwd(char pwd[PATH_MAX]);
void	increment_shlvl(void);
char	*get_var(char *name, char **lst_var, int keyval);

#endif
