/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthan <dthan@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/06 17:32:15 by dthan             #+#    #+#             */
/*   Updated: 2020/09/26 03:00:40 by dthan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H
# include <unistd.h>
# include <stdint.h>
# include <stdlib.h>

int		ft_isdigit(int c);
size_t	ft_strlen(const char *s);
char	*ft_strchr(const char *s, int c);
char	*ft_strdup(const char *s1);
void	*ft_memset(void *s, int c, size_t n);
void	*ft_memalloc(size_t size);
void	ft_bzero(void *s, size_t n);
char	*ft_itoa_signed_longlong(long long n);
char	*ft_itoa_unsigned_longlong(unsigned long long nbr);
char	*ft_strjoin(char const *string1, char const *string2);
char	*ft_strjoin_and_free_string1(char *string1, char *string2);
char	*ft_strjoin_and_free_string2(char *string1, char *string2);
char	*ft_strcpy(char *dst, const char *src);
char	*ft_strcat(char *dest, const char *src);
char	*ft_strnew(size_t size);
int		ft_strcmp(const char *s1, const char *s2);
char	*ft_strncpy(char *dst, const char *src, size_t len);
int		ft_toupper(int c);
int		ft_isalnum(int c);
char	*ft_strrev(char *str);

#endif
