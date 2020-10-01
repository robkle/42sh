/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_redirect.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthan <dthan@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/02 02:26:01 by tango             #+#    #+#             */
/*   Updated: 2020/10/01 06:01:54 by dthan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void			handle_redirect(t_list *list, t_process *p)
{
	t_list *ptr;
	t_redirect *redi;

	ptr = list;
	while (ptr)
	{
		redi = ptr->content;
		if (ft_strequ(redi->redirect_op, ">"))
			redirect_great(redi, p);
		else if (ft_strequ(redi->redirect_op, ">>"))
			redirect_dgreat(redi, p);
		else if (ft_strequ(redi->redirect_op, "<"))
			redirect_less(redi, p);
		else if (ft_strequ(redi->redirect_op, "<<"))
			redirect_dless(redi, p);
		else if (ft_strequ(redi->redirect_op, ">&"))
			redirect_greatand(redi, p);
		else if (ft_strequ(redi->redirect_op, "<&"))
			redirect_lessand(redi, p);
		ptr = ptr->next;
	}
}
