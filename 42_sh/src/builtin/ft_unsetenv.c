/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unsetenv.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthan <dthan@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/03 18:41:57 by ihwang            #+#    #+#             */
/*   Updated: 2020/09/30 05:15:25 by dthan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static int	del_replace(int index)
{
	int		nb;
	int		i;
	int		j;
	char	**temp;

	nb = -1;
	while (g_env[++nb])
		NULL;
	if ((temp = (char**)malloc(sizeof(char*) * nb)) == NULL)
		return (EXIT_FAILURE);
	i = -1;
	j = 0;
	while (++i < nb)
	{
		if (i != index)
		{
			if ((temp[j] = (char*)malloc(PATH_MAX)) == NULL)
				return (EXIT_FAILURE);
			ft_strcpy(temp[j++], g_env[i]);
		}
	}
	temp[j] = NULL;
	ft_strlst_del(&g_env, nb + 1);
	g_env = temp;
	return (EXIT_SUCCESS);
}

static int	is_env(char *str)
{
	int		i;
	char	*dot;

	i = -1;
	while (g_env[++i])
	{
		dot = ft_strchr(g_env[i], '=');
		*dot = '\0';
		if (!ft_strcmp(g_env[i], str))
		{
			*dot = '=';
			return (i);
		}
		*dot = '=';
	}
	return (0);
}

int			ft_unsetenv(t_process *c)
{
	int		i;
	int		j;
	int		index;

	i = 0;
	while (++i < c->ac)
	{
		j = -1;
		while (ft_isalnum(c->av[i][++j]))
			NULL;
		if (c->av[i][j] != '\0')
		{
			error_monitor("unsetenv: '", c->av[i], \
					"': not a valid identifier", EXIT_FAILURE);
			return (EXIT_FAILURE);
		}
		else if ((index = is_env(c->av[i])))
		{
			return (del_replace(index));
		}
	}
	return (EXIT_FAILURE);
}
