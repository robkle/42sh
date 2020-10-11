/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_io_redirect.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthan <dthan@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/01 06:04:12 by dthan             #+#    #+#             */
/*   Updated: 2020/10/02 02:29:42 by dthan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	execute_io_redirect(t_astnode *ast, t_list **hd , t_process *p)
{
	t_redirect		redi;
	t_list *node;
	if (ast->left->type == AST_io_file)
	{
		redi.redirect_op = ast->left->data;
		if (ft_strequ(redi.redirect_op, "<") ||
			ft_strequ(redi.redirect_op, "<&"))
		{
			redi.redirect_src = ast->left->left->data;
			redi.redirect_des = ast->data;
		}
		else
		{
			redi.redirect_src = ast->data;
			redi.redirect_des = ast->left->left->data;
		}
	}
	else if (ast->left->type == AST_io_here)
	{
		redi.redirect_op = ast->left->data;
		redi.redirect_src = (char*)(*hd)->content;
		redi.redirect_des = ast->data;
		*hd = (*hd)->next;
	}
	node = ft_lstnew(&redi, sizeof(t_redirect));
	if (p->redi == NULL)
		p->redi = node;
	else
		ft_lstadd_tail(&(p->redi), node);
}
