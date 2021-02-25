/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_assignment_word.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthan <dthan@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/09 01:57:55 by dthan             #+#    #+#             */
/*   Updated: 2021/02/25 05:57:38 by dthan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

// void	execute_assignment_word(t_astnode *ast)
// {
// 	char	*str;
// 	t_var	*intern_var;
// 	t_var	*ptr;

// 	str = ast->data;
// 	intern_var = (t_var*)ft_memalloc(sizeof(t_var));
// 	intern_var->name = ft_strndup(str, ft_strchr(str, '=') - &str[0]);
// 	intern_var->value = ft_strdup(ft_strchr(str, '=') + 1);
// 	if (ft_getenv(intern_var->name))
// 		intern_var->exported = 1;
// 	else if ((ptr = ft_getvar(intern_var->name)) != NULL && ptr->exported == 1)
// 		intern_var->exported = 1;
// 	else
// 		intern_var->exported = 0;
// 	if (is_intern_var(intern_var->name))
// 		update_intern_var(intern_var);
// 	else
// 		add_intern_var(intern_var);
// }

void	execute_assignment_word(t_astnode *ast, t_process *p)
{
	t_assignment *assignment_word;
	t_assignment *ptr;

	ptr = p->first_assignment;
	assignment_word = (t_assignment*)ft_memalloc(sizeof(t_assignment));
	assignment_word->data = ft_strdup(ast->data);
	assignment_word->next = NULL;
	if (ptr == NULL)
		p->first_assignment = assignment_word;
	else
	{
		while (ptr->next)
			ptr = ptr->next;
		ptr->next = assignment_word;
	}
}
