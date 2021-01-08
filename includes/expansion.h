/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthan <dthan@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/17 13:07:00 by dthan             #+#    #+#             */
/*   Updated: 2020/12/30 14:29:37 by dthan            ###   ########.fr       */
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

#endif