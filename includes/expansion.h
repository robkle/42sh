/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthan <dthan@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/17 13:07:00 by dthan             #+#    #+#             */
/*   Updated: 2021/01/27 12:20:27 by dthan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANSION_H
# define EXPANSION_H
# include "struct.h"

char					replace_hex_value(char *str);
int						is_eight_bit_character_whose_value_is_hexadecimal_value(
	char *str);

char					replace_octal_value(char *str);
int						is_eight_bit_character_whose_value_is_octal_value(
	char *str);

char					replace_ansi_c_quoting(char c);
int						is_ansi_c_quoting(char *str);

int						quote_removal(t_process *p);
int						handle_expansion(t_process *p);

/*
** ========================= parameter expansion ==============================
*/

int						parameter_expansion_in_redi(t_process *p);
int						parameter_expansion_in_av(t_process *p);

/*
** parameter expansion struct
*/

t_parameter_expansion	*constructor_parameter_expansion_struct(
	char *str);
void					destructor_parameter_expansion_struct(
	t_parameter_expansion *self);
void					parameter_expansion_struct_split(
	t_parameter_expansion *self);
int						parameter_expansion_syntax_analysis(
	t_parameter_expansion *self);
int						parameter_expansion_struct_replacement(
	char replacement[256], t_parameter_expansion *self);
int						parameter_expansion_colon_minus_case(
	char parameter[256], char word[256], char replacement[256],
	t_parameter_expansion_type type);
int						parameter_expansion_colon_equal_case(
	char parameter[256], char word[256], char replacement[256],
	t_parameter_expansion_type type);
int						parameter_expansion_colon_question_case(
	char parameter[256], char word[256], char replacement[256],
	t_parameter_expansion_type type);
int						parameter_expansion_colon_plus_case(
	char word[256], char replacement[256], t_parameter_expansion_type type);
int						parameter_expansion_percent_case(
	char parameter[256], char word[256], char replacement[256],
	t_parameter_expansion_type type);
int						parameter_expansion_h(
	char parameter[256], char word[256], char replacement[256],
	t_parameter_expansion_type type);
/*
** parameter expansion tools
*/

char					*parameter_expansion_tool_replace(
	char *target, char *needle, char *replacement);
int						jump_expansion(
	char *str, int *i, char expansion_type, char temp[2]);
int						is_parameter_expansion(char *str);
void					substitute_parameter(
	char parameter[256], char replacement[256]);
void					substitute_word(
	char word[256], char replacement[256]);
void					assign_word(
	char parameter[256], char word[256]);
void					remove_smallest_or_largest_suffix_pattern(
	char parameter[256], char word[256], char replacement[256]);
void					remove_smallest_or_largest_prefix_pattern(
	char parameter[256], char word[256], char replacement[256]);


/*
** tilde expansion
*/

int tilde_expansion(t_process *p);

#endif
