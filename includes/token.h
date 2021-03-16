/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthan <dthan@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/07 07:58:26 by dthan             #+#    #+#             */
/*   Updated: 2021/03/14 02:48:06 by dthan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKEN_H
# define TOKEN_H
# include "struct.h"

/*
** Checking tools
*/

int		is_metacharacter(char chr);
int		is_valid_operator_token(char *str);
int		is_unsupported_tokens(t_token_type type);
int		is_control_op_not_newline(t_token_type type);
int		is_redirect_op(t_token_type type);
int		is_control_op(t_token_type type);
int		is_assignment_token(char *str, t_token *prev_token);
int		is_inhibitors(char *input, int i, char ch);
int		is_expansion(char *input, int i, char ch);
int		is_open_curly_bracket_for_parameter_expansion(
	char *str, int i, t_phase phase[], int stack_pos);
int		is_open_parenthesis_for_arthimetic_expansion(
	char *str, int i, t_phase phase[], int stack_pos);

/*
** Create token tools
*/

t_token *non_operator_token(char *data, t_token_type type);
t_token	*get_operator_token(char *input, int *i);
t_token *get_non_operator_token(char *input, int *i, t_token *prev_tk);
t_token *token_creator_service(char *input, int *i, t_token *prev_tk);

/*
** other tools
*/
void	add_token_into_token_list(t_token **token_lst, t_token *new);
void	clear_token(t_token *token);
t_token *find_prev_token_in_new_stream(t_token *tk_lst);
t_token *find_current_token_in_new_stream(t_token *tk_lst);

/*
** Debug
*/
void	print_token(t_token *token);

#endif
