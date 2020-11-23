/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthan <dthan@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/07 07:58:26 by dthan             #+#    #+#             */
/*   Updated: 2020/10/27 05:31:25 by dthan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKEN_H
# define TOKEN_H

typedef enum
{
	TOKEN_APS, // &		control op
	TOKEN_SEMI, // ;	control op
	TOKEN_PIPE, // |	control	op
	TOKEN_OB, // (  // not support
	TOKEN_CB, // )   //not support
	TOKEN_WORD,
	TOKEN_ASSIGNMENT_WORD, //not support
	TOKEN_NAME, // not support
	TOKEN_NEWLINE, // not yet, it depends
	TOKEN_IO_NUMBER,
	TOKEN_AND_IF, // &&		control op
	TOKEN_OR_IF, // ||		control op
	TOKEN_DSEMI, // ;;  // not support
	TOKEN_GREAT, // >						reidrect op
	TOKEN_DGREAT, // >>						redirect op
	TOKEN_LESS, // <						redirect op
	TOKEN_DLESS, // <<						redirect op
	TOKEN_LESSAND, // <&					redirect op
	TOKEN_GREATAND, // >&					redirect op
	TOKEN_LESSGREAT, // <>  // not support
	TOKEN_DLESSDASH, // <<- // not support
	TOKEN_CLOBBER, // >|  // not support
}	t_token_type;

typedef struct			s_token
{
	char				*data;
	t_token_type		type;
	struct s_token		*next;
}						t_token;

t_token	*lexer_and_parser(char *input);
int		is_metacharacter(char chr);
int		is_valid_operator_token(char *str);
int		is_unsupported_tokens(t_token_type type);
int		is_control_op_not_newline(t_token_type type);
int		is_redirect_op(t_token_type type);
int		is_made_of_digits(char *data);
void	add_token_into_token_list(t_token **token_lst, t_token *new);
void	clear_token(t_token *token);
void	print_token(t_token *token); //debug
t_token	*get_non_operator_token(char *input, int *i);
t_token *non_operator_token(char *data, t_token_type type);
t_token	*get_operator_token(char *input, int *i);

#endif
