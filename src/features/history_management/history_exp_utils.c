/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history_exp_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rklein <rkelin@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/19 16:00:03 by rklein            #+#    #+#             */
/*   Updated: 2021/02/19 16:15:16 by rklein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int		ft_str_search(char *str)
{
	int	i;

	i = g_shell.history->curr;
	while (--i >= 0)
	{
		if (ft_strnequ(str, g_shell.history->hist[i], ft_strlen(str)))
			return (i);
	}
	return (-1);
}

void	ft_hist_exp_quote(char c, int *q, t_prompt pr)
{
	if (pr == PROMPT_QUOTE)
		*q = 1;
	else if (pr == PROMPT_QUOTE)
		*q = 2;
	else if (c == 39 && *q != 2)
		*q = !*q ? 1 : 0;
	else if (c == 34 && *q != 1)
		*q = !*q ? 2 : 0;
}
