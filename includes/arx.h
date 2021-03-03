/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arx.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rklein <rklein@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/19 12:36:51 by rklein            #+#    #+#             */
/*   Updated: 2021/03/01 11:06:50 by rklein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ARX_H
# define ARX_H

# define XBUF 8
# define INVOP 1
# define VTGFB 2
# define OPEXP 3
# define INVBA 4
# define INVNU 5
# define SNERR 6
# define BVL "0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ@_"

typedef struct	s_st
{
	char		*op;
	char		*type;
	struct s_st	*prev;
	struct s_st	*next;
}				t_st;

typedef enum	e_pr
{
	SU,
	UNPR,
	MDM,
	AS,
	RO,
	EO,
	LA,
	LO,
	INVALID
}				t_pr;

/*
** arx.c
*/
int				ft_arx(t_process *p);
int				ft_arx_lexer(char *arx, long long int *res);

/*
** arx_exp.c
*/
int				ft_expand_arx(char *arx, long long int *res);

/*
** arx_lexer.c
*/
int				ft_arx_final_result(char **arx_token, long long int *res);
int				ft_arx_token_exp(char **arx_token, long long int *res);
int				ft_bracket_check(char *exp, int	qc);
char			**ft_expsplit(char *arx);
void			ft_arx_token_move(char **arx_token, int i);

/*
** atoi_base.c
*/
int				ft_atoi_base(t_st *infix, char *value, int base, int calc);

/*
** base.c
*/
int				ft_base(t_st *infix, t_st *begin, int calc);
void			ft_base_calc(t_st *infix);

/*
** calc.c
*/
char			*ft_calc(t_st *postfix);

/*
** checker.c
*/
t_st			*ft_infix_checker(t_st *infix);

/*
** error.c
*/
void			ft_print_error(int error, t_st *infix, t_st *expr);

/*
** extolst.c
*/
int				ft_operator(char c);
t_st			*ft_extolst(char *exp);

/*
** infix_format.c
*/
void			ft_infix_format(t_st **infix);

/*
** intvar.c
*/
void			ft_intvar(t_st *stack, char *op);

/*
** operand.c
*/
void			ft_operand(t_st **infix);

/*
** plusminus.c
*/
void			ft_plusminus(t_st **infix);

/*
** postfix.c
*/
char			*ft_postfix(char *exp);
int				ft_operator_str(char *op);
void			ft_itop_lst(t_st *infix, t_st **postfix);

/*
** utils.c
*/
void			ft_modify_link(t_st *infix, char *op, char *type);
void			ft_pop_stack(t_st **stack);
void			ft_push_lst(t_st **infix, char *op, char *type);
void			ft_push_stack(t_st **stack, char *op, char *type);
t_st			*ft_last_link(t_st *lst);

/*
** utils_exp.c
*/
int				ft_expansion_len(char *exp);
char			**ft_split_arx(char *arx, int index, int len);
char			*ft_strcombine(char **exp, char *res);
int				ft_arx_brackets(char *exp);
void			ft_free_lst(t_st **lst);

/*
** utils_exp2.c
*/
int				ft_update_arx(char **arx, char **exp, int res);
int				ft_arx_free_exp(char **exp, char *arx);
int				ft_arx_free_exp_bracket(char *arx);

/*
** utils_format.c
*/
void			ft_free_link(t_st *link);
void			ft_arx_skip_link(t_st *infix);

/*
** utils_pm.c
*/
t_st			*ft_skip_space(t_st *link, const int move);
int				ft_isunary(t_st *infix);
int				ft_issuf(t_st *infix);
int				ft_ispre(t_st *infix);
int				ft_pref_suf_check(t_st *infix, t_st *begin);

#endif
