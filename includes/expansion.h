/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthan <dthan@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/17 13:07:00 by dthan             #+#    #+#             */
/*   Updated: 2021/01/27 08:09:19 by dthan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANSION_H
# define EXPANSION_H
# include "struct.h"


char replace_hex_value(char *str);
int is_eight_bit_character_whose_value_is_hexadecimal_value(char *str);

char replace_octal_value(char *str);
int is_eight_bit_character_whose_value_is_octal_value(char *str);

char replace_ansi_c_quoting(char c);
int is_ansi_c_quoting(char *str);

int quote_removal(t_process *p);
int handle_expansion(t_process *p);

// int jump_parameter(char *input, int *i); // need to delete
// int is_real_parameter_expansion(char *str, int i); // need to delete
// int is_real_dolar_sign(char *str, int i); // need to delete


// parameter expansion
int parameter_expansion_in_redi(t_process *p);
int parameter_expansion_in_av(t_process *p);
t_parameter_expansion *constructor_parameter_expansion_struct(char *str);
void destructor_parameter_expansion_struct(t_parameter_expansion *self);

char *parameter_expansion_tool_replace(char *target, char *needle, char *replacement);
int jump_expansion(char *str, int *i, char expansion_type, char temp[2]);
int is_parameter_expansion(char *str);
void substitute_parameter(char parameter[256], char replacement[256]);
void substitute_word(char word[256], char replacement[256]);
void assign_word(char parameter[256], char word[256]);
void remove_smallest_or_largest_suffix_pattern(char parameter[256], char word[256], char replacement[256]);
void remove_smallest_or_largest_prefix_pattern(char parameter[256], char word[256], char replacement[256]);

#endif