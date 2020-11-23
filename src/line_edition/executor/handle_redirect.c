/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_redirect.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthan <dthan@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/02 02:26:01 by tango             #+#    #+#             */
/*   Updated: 2020/10/30 05:34:43 by dthan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int	handle_redirection(t_list *redirection_list, t_process *p)
{
	t_list *ptr;
	t_redi *redi;
	int ret;

	if (redirection_list == NULL)
		return (EXIT_SUCCESS);
	ptr = redirection_list;
	ret = EXIT_SUCCESS;
	while (ptr && ret == EXIT_SUCCESS)
	{
		redi = ptr->content;
		if (ft_strequ(redi->op, ">"))
			ret = redirect_great(redi, p);
		else if (ft_strequ(redi->op, ">>"))
			ret = redirect_dgreat(redi, p);
		else if (ft_strequ(redi->op, ">&"))
			ret = redirect_greatand(redi, p);
		else if (ft_strequ(redi->op, "<"))
			ret = redirect_less(redi, p);
		else if (ft_strequ(redi->op, "<<"))
			ret = redirect_dless(redi, p);
		else if (ft_strequ(redi->op, "<&"))
			ret = redirect_lessand(redi, p);
		ptr = ptr->next;
	}
	return (ret);
}
