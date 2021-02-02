/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthan <dthan@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/07 07:58:26 by dthan             #+#    #+#             */
/*   Updated: 2021/01/09 03:21:05 by dthan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKEN_H
# define TOKEN_H
# include "struct.h"

t_token	*lexer_and_parser(char *input);
int		is_metacharacter(char chr);
int		is_valid_operator_token(char *str);
int		is_unsupported_tokens(t_token_type type);
int		is_control_op_not_newline(t_token_type type);
int		is_redirect_op(t_token_type type);
int		is_made_of_digits(char *data);
int		parser(t_token *curr, t_token *prev);
void	add_token_into_token_list(t_token **token_lst, t_token *new);
void	clear_token(t_token *token);
void	print_token(t_token *token); //debug
t_token	*get_non_operator_token(char *input, int *i);
t_token *non_operator_token(char *data, t_token_type type);
t_token	*get_operator_token(char *input, int *i);
int is_assignment_token(char *str, t_token *prev_token);
#endif
