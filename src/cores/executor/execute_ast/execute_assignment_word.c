/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_assignment_word.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthan <dthan@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/09 01:57:55 by dthan             #+#    #+#             */
/*   Updated: 2021/01/15 10:41:21 by dthan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void execute_assignment_word(t_astnode *ast)
{
	char *str;
	t_var *intern_var;
	t_var *ptr;

	str = ast->data;
	intern_var = (t_var*)ft_memalloc(sizeof(t_var));
	intern_var->name = ft_strndup(str, ft_strchr(str, '=') - &str[0]);
	intern_var->value = ft_strdup(ft_strchr(str, '=') + 1);
	if (ft_getenv(intern_var->name))
		intern_var->exported = 1;
	else if ((ptr = ft_getvar(intern_var->name)) != NULL && ptr->exported == 1)
		intern_var->exported = 1;
	else
		intern_var->exported = 0;
	if (is_intern_var(intern_var->name))
		update_intern_var(intern_var);
	else
		add_intern_var(intern_var);
}
