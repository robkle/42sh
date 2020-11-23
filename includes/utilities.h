/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilities.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthan <dthan@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/13 11:35:45 by dthan             #+#    #+#             */
/*   Updated: 2020/11/03 11:31:52 by dthan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILITIES_H
# define UTILITIES_H
# include <string.h>
# include "shell.h"

int		is_open_dquote(char *input, int level, char *quote);
int		is_made_of_digits(char *data);
int		input_contain_dquote(char *input);
char	*ft_strjoin_and_free_string2(char *string1, char *string2);
char	*ft_strjoin_and_free_string1(char *string1, char *string2);
int 	set_oldpwd(char pwd[PATH_MAX]);
void	increment_shlvl(void);
char	*get_env(char *name, int keyval);
int		ft_isspace(int c);
char	*ft_strndup(char *str, size_t len);
void	ft_arraydel(char **string_array);
int 	ft_lstlen(t_list *head);
void	jump_quote(char *input, int *i, char quote_type);
int	ft_strncmp(const char *s1, const char *s2, size_t n);

#endif
