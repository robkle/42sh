/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_redirect.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthan <dthan@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/02 02:26:01 by tango             #+#    #+#             */
/*   Updated: 2020/12/18 18:17:46 by dthan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int	handle_redirection(t_process *p)
{
	t_redi *redi_ptr;
	int ret;

	if (p->first_redi == NULL)
		return (EXIT_SUCCESS);
	redi_ptr = p->first_redi;
	ret = EXIT_SUCCESS;
	while (redi_ptr && ret == EXIT_SUCCESS)
	{
		if (ft_strequ(redi_ptr->op, ">"))
			ret = redirect_great(redi_ptr);
		else if (ft_strequ(redi_ptr->op, ">>"))
			ret = redirect_dgreat(redi_ptr);
		else if (ft_strequ(redi_ptr->op, ">&"))
			ret = redirect_greatand(redi_ptr);
		else if (ft_strequ(redi_ptr->op, "<"))
			ret = redirect_less(redi_ptr);
		else if (ft_strequ(redi_ptr->op, "<<"))
			ret = redirect_dless(redi_ptr);
		else if (ft_strequ(redi_ptr->op, "<&"))
			ret = redirect_lessand(redi_ptr);
		redi_ptr = redi_ptr->next;
	}
	return (ret);
}
