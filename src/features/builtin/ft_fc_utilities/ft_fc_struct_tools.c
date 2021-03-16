/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fc_struct_tools.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthan <dthan@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/13 13:44:21 by dthan             #+#    #+#             */
/*   Updated: 2021/03/13 13:49:08 by dthan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	init_ft_fc_struct(t_ft_fc *self)
{
	self->ops = 0;
	self->editor = ft_strdup(DEFAULT_EDITOR);
	self->blocks[FIRST] = NULL;
	self->blocks[LAST] = NULL;
	self->blocks[REPLACE] = NULL;
}

void	clean_up_ft_fc_struct(t_ft_fc instance)
{
	(instance.editor) ? free(instance.editor) : 0;
	(instance.blocks[FIRST]) ? free(instance.blocks[FIRST]) : 0;
	(instance.blocks[LAST]) ? free(instance.blocks[LAST]) : 0;
	(instance.blocks[REPLACE]) ? free(instance.blocks[REPLACE]) : 0;
}
