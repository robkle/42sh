/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthan <dthan@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/15 09:47:30 by dthan             #+#    #+#             */
/*   Updated: 2021/01/15 11:15:51 by dthan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int export_error_invalid_option(char c)
{
	ft_dprintf(2, "%s: export: -%c: invalid option\n", SHELL_NAME, c);
	ft_dprintf(2, "export: usage: export name[=value]... or export -p\n");
	return (EXIT_FAILURE);
}

int export_error_not_a_valid_identifier(char *str)
{
	ft_dprintf(2, "%s: export: `%s': not a valid identifier\n", SHELL_NAME, str);
	return (EXIT_FAILURE);
}

int export_parse_flag(t_export *export, char *str)
{
	int i;

	i = -1;
	while(str[++i])
	{
		if (ft_strchr(export->opt_set, str[i]))
			export->opt |= EXPORT_OPT_P;
		else
			return (export_error_invalid_option(str[i]));
	}
	return (EXIT_SUCCESS);
}

int export_parse_var(char *str)
{
	char name[4096];
	char value[4096];
	int i;

	ft_bzero(name, 4096);
	ft_bzero(value, 4096);
	if (ft_strchr(str, '='))
	{
		ft_strncpy(name, str, ft_strchr(str, '=') - &str[0]);
		ft_strcpy(value, ft_strchr(str, '=') + 1);
	}
	else
		ft_strcpy(name, str);
	if (name[0] && !ft_isalpha(name[0]))
		return (export_error_not_a_valid_identifier(str));
	i = -1;
	while (name[++i])
		if (!ft_isalnum(name[i]))
			return (export_error_not_a_valid_identifier(str));
	return (EXIT_SUCCESS);
}

/*
** synopsis 0 - the beginning
** synopsis 1 - export name[=word]...
** synopsis 2 - export -p
*/

int export_parse_av(t_export *export, char **av)
{
	int i;
	int j;

	i = 0;
	while(av[++i] && av[i][0] == '-')
	{
		export->synopsis = 1;
		if (export_parse_flag(export, &av[i][1]) == EXIT_FAILURE)
			return (EXIT_FAILURE);
	}
	if (av[i])
	{
		export->synopsis = 2;
		j = 0;
		while(av[i])
		{
			if (export_parse_var(av[i]) == EXIT_FAILURE)
				return (EXIT_FAILURE);
			export->av[j++] = av[i++];
		}
	}
	return (EXIT_SUCCESS);
}

int ft_export_print(void)
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

int ft_export_export(char **av)
{
	int i;
	t_var *var_temp;
	char name[4096];
	char value[4096];

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
		if (ft_strchr(av[i], '='))
			var_temp->value = ft_strdup(value);
		else
			var_temp->value = NULL;
		if (is_intern_var(var_temp->name))
			update_intern_var(var_temp);
		else
			add_intern_var(var_temp);			
	}
	return (EXIT_SUCCESS);
}

int ft_export(int ac, char **av)
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
		return(ft_export_print());
	return (ft_export_export(export.av));
}
