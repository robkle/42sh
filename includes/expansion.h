/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthan <dthan@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/17 13:07:00 by dthan             #+#    #+#             */
/*   Updated: 2020/12/26 11:35:23 by dthan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANSION_H
# define EXPANSION_H
# include "struct.h"

int quote_removal(t_process *p);
int handle_expansion(t_process *p);

#endif