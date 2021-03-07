/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_assignment_word.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthan <dthan@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/09 01:57:55 by dthan             #+#    #+#             */
/*   Updated: 2021/03/07 15:53:51 by dthan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

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
