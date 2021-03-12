/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_parse.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthan <dthan@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/12 23:07:34 by dthan             #+#    #+#             */
/*   Updated: 2021/03/12 23:12:33 by dthan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static int	export_error_invalid_option(char c)
{
	ft_dprintf(2, "%s: export: -%c: invalid option\n", SHELL_NAME, c);
	ft_dprintf(2, "export: usage: export name[=value]... or export -p\n");
	return (EXIT_FAILURE);
}

static int	export_error_not_a_valid_identifier(char *str)
{
	ft_dprintf(2, "%s: export: `%s': not a valid identifier\n",
		SHELL_NAME,
		str);
	return (EXIT_FAILURE);
}

static int	export_parse_flag(t_export *export, char *str)
{
	int i;

	i = -1;
	while (str[++i])
	{
		if (ft_strchr(export->opt_set, str[i]))
			export->opt |= EXPORT_OPT_P;
		else
			return (export_error_invalid_option(str[i]));
	}
	return (EXIT_SUCCESS);
}

static int	export_parse_var(char *str)
{
	char	name[4096];
	char	value[4096];
	int		i;

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

int			export_parse_av(t_export *export, char **av)
{
	int i;
	int j;

	i = 0;
	while (av[++i] && av[i][0] == '-')
	{
		export->synopsis = 1;
		if (export_parse_flag(export, &av[i][1]) == EXIT_FAILURE)
			return (EXIT_FAILURE);
	}
	if (av[i])
	{
		export->synopsis = 2;
		j = 0;
		while (av[i])
		{
			if (export_parse_var(av[i]) == EXIT_FAILURE)
				return (EXIT_FAILURE);
			export->av[j++] = av[i++];
		}
	}
	return (EXIT_SUCCESS);
}
