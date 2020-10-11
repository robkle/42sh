/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihwang <ihwang@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/03 18:41:57 by ihwang            #+#    #+#             */
/*   Updated: 2020/10/10 18:14:04 by ihwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "builtin.h"

static int	del_replace(int index, char ***lst_var)
{
	int		nb;
	int		i;
	int		j;
	char	**temp;

	nb = -1;
	while ((*lst_var)[++nb])
		NULL;
	if ((temp = (char**)malloc(sizeof(char*) * nb)) == NULL)
		return (FALSE);
	i = -1;
	j = 0;
	while (++i < nb)
	{
		if (i != index)
		{
			if ((temp[j] = (char*)malloc(PATH_MAX)) == NULL)
				return (FALSE);
			ft_strcpy(temp[j++], (*lst_var)[i]);
		}
	}
	temp[j] = NULL;
	ft_strlst_del(lst_var, nb + 1);
	*lst_var = temp;
	return (TRUE);
}

static int	is_var(char *str, char **lst_var)
{
	int		i;
	int		pos_equ;

	i = -1;
	while (lst_var[++i])
	{
		pos_equ = (int)(ft_strchr(lst_var[i], '=') - lst_var[i]);
		if (ft_strnequ(lst_var[i], str, pos_equ) && \
			pos_equ == (int)ft_strlen(str))
			return (i);
	}
	return (-1);
}

static char	*create_errmsg(char *target, char *msg)
{
	if (ft_strequ(msg, "success"))
	{
		ft_strdel(&msg);
		msg = ft_strdup("42sh: unset: `");
	}
	else
		msg = ft_strjoin(msg, "\n42sh: unset: `");
	msg = ft_strjoin(msg, target);
	msg = ft_strjoin(msg, "\': not a valid identifier\n");
	return (msg);
}

char		*ft_unset(t_process *c, char ***lst_var)
{
	int		i;
	int		j;
	int		index;
	char	*ret;

	i = 0;
	ret = ft_strdup("success");
	while (++i < c->ac)
	{
		j = -1;
		while (ft_isalnum(c->av[i][++j]))
			NULL;
		if (c->av[i][j] != '\0')
			ret = create_errmsg(c->av[i], ret);
		else if ((index = is_var(c->av[i], *lst_var)) > -1)
			del_replace(index, lst_var);
		else if (*lst_var == g_shell.env && \
			(index = is_var(c->av[i], g_shell.var)) > -1)
			del_replace(index, &g_shell.var);
	}
	return (ret);
}
