/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tilde_expansion.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgrankul <vgrankul@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/25 07:42:54 by vgrankul          #+#    #+#             */
/*   Updated: 2021/01/25 07:42:59 by vgrankul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

char	*get_login_value(char *t_prefix)
{
	struct passwd *login;

	login = getpwnam(t_prefix);
	if (login != NULL)
		return (ft_strdup(login->pw_dir));
	return (NULL);
}

int		tilde_prefix_len(char *word)
{
	int i;

	i = 0;
	if (word[0] == '~')
	{
		while (word[i] != '/' && word[i] != ':' && word[i] != '\0')
		{
			if (word[i] == '"' || word[i] == '\'')
			{
				i++;
				while (word[i] != '\0' && (word[i] != '"' && word[i] != '\''))
					i++;
			}
			i++;
		}
	}
	return (i);
}

char	*get_value(char *t_prefix)
{
	char *value;

	if ((ft_strcmp(t_prefix, "~/") == 0 || ft_strcmp(t_prefix, "~") == 0) &&
		(value = ft_getenv("HOME")) != NULL)
		return (ft_strdup(value));
	else if (ft_strcmp(t_prefix, "~+") == 0 &&
		(value = ft_getenv("PWD")) != NULL)
		return (ft_strdup(value));
	else if (ft_strcmp(t_prefix, "~-") == 0 &&
		(value = ft_getenv("OLDPWD")) != NULL)
		return (ft_strdup(value));
	return (value = get_login_value(&t_prefix[1]));
}
