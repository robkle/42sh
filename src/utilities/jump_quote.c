/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jump_quote.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthan <dthan@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/30 06:30:22 by dthan             #+#    #+#             */
/*   Updated: 2020/10/30 06:30:42 by dthan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void jump_quote(char *input, int *i, char quote_type)
{
	while(input[*i] && input[*i] != quote_type)
		(*i)++;
}
