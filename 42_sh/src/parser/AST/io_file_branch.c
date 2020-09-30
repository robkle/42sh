/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   io_file_branch.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthan <dthan@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/11 10:16:43 by dthan             #+#    #+#             */
/*   Updated: 2020/09/30 05:22:16 by dthan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

t_astnode	*io_file(t_token **token)
{
	if (*token == NULL)
		return (NULL);
	if (ft_strcmp((*token)->data, "<") == 0)
		return (io_file1(token));
	if (ft_strcmp((*token)->data, "<&") == 0)
		return (io_file2(token));
	if (ft_strcmp((*token)->data, ">") == 0)
		return (io_file3(token));
	if (ft_strcmp((*token)->data, ">&") == 0)
		return (io_file4(token));
	if (ft_strcmp((*token)->data, ">>") == 0)
		return (io_file5(token));
	// if (ft_strcmp((*token)->data, "<<") == 0)
	// 	return (io_file6(token));
	return (NULL);
}
