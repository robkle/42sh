/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilities.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthan <dthan@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/13 11:35:45 by dthan             #+#    #+#             */
/*   Updated: 2020/12/27 17:41:00 by dthan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILITIES_H
# define UTILITIES_H

# include <stdlib.h>
# include "libft.h"
# include "struct.h"

int		is_open_dquote(char *input, int level, char *quote);
int		is_made_of_digits(char *data);
int		input_contain_dquote(char *input);
char	*ft_strjoin_and_free_string2(char *string1, char *string2);
char	*ft_strjoin_and_free_string1(char *string1, char *string2);
char	*ft_strjoin_and_free_2strings(char *string1, char *string2);
void	increment_shlvl(void);
int		ft_isspace(int c);
char	*ft_strndup(char *str, size_t len);
void	ft_arraydel(char **string_array);
int		ft_strstr_int(const char *haystack, const char *needle);
int		ft_strchr_int(char *str, int c);
int		ft_num_check(char *str);
void	ft_swap(int *nums);
int 	ft_lstlen(t_list *head);
void	jump_quote(char *input, int *i, char quote_type);
int	ft_strncmp(const char *s1, const char *s2, size_t n);
char *ft_getenv(const char *name);
char *ft_getvar(const char *name);
char *ft_strbuilder(int argc, char *str, ...);
char *ft_strbuilder_char(char *old, char c);
int ft_tcsetpgrp (int fd, pid_t pgrp_id);
pid_t ft_tcgetpgrp (int fd);
int		ft_isspace(int c);
void	ft_arraydel(char **string_array);
void		check_builtin_opts(char **av, t_opt *opt);
void		init_opt(t_opt *opt, const char *opt_set);

/*
** Deprecated utility functions && macros
*/

# define KEY 1
# define VAL 0

char	*get_var(char *name, char **lst_var, int keyval);

#endif
