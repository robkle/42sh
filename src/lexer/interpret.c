/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interpret.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihwang <ihwang@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/06 15:28:10 by ihwang            #+#    #+#             */
/*   Updated: 2020/10/11 07:14:33 by ihwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "utilities.h"

void		interpret_tild(char **str)
{
	char		*home;
	char		*new_str;

	if (str[0][0] == '~' && (str[0][1] == '\0' || str[0][1] == '/'))
	{
		home = get_var("HOME", g_shell.env, VAL);
		new_str = (char*)malloc(ft_strlen(home) + ft_strlen(*str) + 1);
		ft_strcpy(new_str, home);
		ft_strcat(new_str, &str[0][1]);
		ft_strdel(str);
		*str = new_str;
	}
}

static void	assign_str_to_node(t_token *node, char *rest, char *target)
{
	char	*temp;

	temp = node->data;
	node->data = ft_strjoin(node->data, get_var(target, g_shell.env, VAL));
	ft_strdel(&temp);
	temp = node->data;
	node->data = ft_strjoin(node->data, rest);
	ft_strdel(&temp);
}

void		interpret_dollar(t_token *node)
{
	int			i;
	int			j;
	char		*rest;
	char		*target;

	i = -1;
	while (node->data[++i])
	{
		if (node->data[i] == '$')
		{
			j = i;
			while (ft_isalnum(node->data[++j]))
				NULL;
			target = ft_strnew(j - i);
			ft_strncpy(target, &(node->data)[i + 1], j - i - 1);
			rest = ft_strdup(&(node->data)[j]);
			node->data[i] = '\0';
			if (get_var(target, g_shell.env, VAL))
				assign_str_to_node(node, rest, target);
			ft_strdel(&rest);
			ft_strdel(&target);
		}
	}
}
