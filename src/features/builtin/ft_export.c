/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthan <dthan@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/15 09:47:30 by dthan             #+#    #+#             */
/*   Updated: 2021/03/12 23:10:01 by dthan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

/*
** synopsis 0 - the beginning
** synopsis 1 - export name[=word]...
** synopsis 2 - export -p
*/

int	ft_export_print(void)
{
	int i;

	i = -1;
	while (g_shell.intern_var[++i])
	{
		if (g_shell.intern_var[i]->exported)
		{
			ft_printf("export %s", g_shell.intern_var[i]->name);
			if (g_shell.intern_var[i]->value)
				ft_printf("=%s\n", g_shell.intern_var[i]->value);
			else
				ft_putchar('\n');
		}
	}
	return (EXIT_SUCCESS);
}

int	ft_export_export(char **av)
{
	int		i;
	t_var	*var_temp;
	char	name[4096];
	char	value[4096];

	i = -1;
	while (av[++i])
	{
		ft_bzero(name, 4096);
		ft_bzero(value, 4096);
		var_temp = (t_var*)ft_memalloc(sizeof(t_var));
		var_temp->exported = 1;
		if (ft_strchr(av[i], '='))
		{
			ft_strncpy(name, av[i], ft_strchr(av[i], '=') - &av[i][0]);
			ft_strcpy(value, ft_strchr(av[i], '=') + 1);
		}
		else
			ft_strcpy(name, av[i]);
		var_temp->name = ft_strdup(name);
		var_temp->value = (ft_strchr(av[i], '=')) ? ft_strdup(value) : NULL;
		(is_intern_var(var_temp->name)) ?
			update_intern_var(var_temp) : add_intern_var(var_temp);
	}
	return (EXIT_SUCCESS);
}

int	ft_export(int ac, char **av)
{
	t_export export;

	(void)ac;
	ft_bzero(&export, sizeof(t_export));
	export.opt_set = ft_strdup(BUILTIN_EXPORT_OPT_SET);
	if (export_parse_av(&export, av) == EXIT_FAILURE)
	{
		free(export.opt_set);
		return (EXIT_FAILURE);
	}
	free(export.opt_set);
	if (export.synopsis == 0 || export.synopsis == 1)
		return (ft_export_print());
	return (ft_export_export(export.av));
}
