/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilities.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthan <dthan@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/13 11:35:45 by dthan             #+#    #+#             */
/*   Updated: 2020/10/05 04:16:18 by dthan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILITIES_H
# define UTILITIES_H

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
int		ft_strstr_int(const char *haystack, const char *needle);
int		ft_strchr_int(char *str, int c);
int		ft_num_check(char *str);
void	ft_swap(int *nums);

#endif
