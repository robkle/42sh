/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fc_utilities.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthan <dthan@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/19 17:55:41 by dthan             #+#    #+#             */
/*   Updated: 2021/03/13 22:50:41 by dthan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

/*
** function fc_find_existing_cmd: find the command in the history list based on
** the string input
** RETURN:  return i > 0 on success
**			return 0 on error, when no matches in the history
*/

static int	fc_find_existing_cmd(char *s)
{
	int i;

	i = g_shell.history->curr;
	while (i > 0)
	{
		if (ft_strnequ(s, g_shell.history->hist[i], ft_strlen(s)))
			return (i);
		i--;
	}
	return (0);
}

/*
** funtion fc_range: find the command in the history, if number is not
** recognized then it will look for the lastest command in the history list
**		PARAM:
**				@ str: the string input
**		RETURN: the position of the command acording to the its postion in the
**				history list
**				Error = 0, if the command not found
*/

int			fc_range(char *str)
{
	int pos;

	if (str)
	{
		if (ft_isdigit(str[0]) ||
			(str[0] == '-' && str[1] && ft_isdigit(str[1])))
			pos = ft_atoi(str);
		else
			return (fc_find_existing_cmd(str));
		if (pos > g_shell.history->curr || pos == 0)
			pos = g_shell.history->curr;
		else if (pos < 0)
		{
			pos = g_shell.history->curr + 1 + pos;
			if (pos < 0)
				pos = 1;
		}
	}
	else
		pos = g_shell.history->curr;
	return (pos);
}

int			ft_num_check(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '-')
		i++;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}
