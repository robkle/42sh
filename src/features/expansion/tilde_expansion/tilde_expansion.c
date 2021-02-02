/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tilde_expansion.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthan <dthan@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/25 07:42:54 by dthan             #+#    #+#             */
/*   Updated: 2021/01/25 07:42:59 by dthan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

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

char	*get_value(char *t_prefix)
{
	char *value;

	if ((ft_strcmp(t_prefix, "~/") == 0 || ft_strcmp(t_prefix, "~") == 0) &&
		(value = ft_getenv("HOME")) != NULL)
		return (value);
	else if (ft_strcmp(&t_prefix[1], (value = ft_getenv("LOGNAME"))) == 0)
	{
		if ((value = ft_getenv("HOME")) != NULL)
			return (value);
	}
	else if (ft_strcmp(t_prefix, "~+") == 0 &&
		(value = ft_getenv("PWD")) != NULL)
		return (value);
	else if (ft_strcmp(t_prefix, "~-") == 0 &&
		(value = ft_getenv("OLDPWD")) != NULL)
		return (value);
	return (NULL);
}

int tilde_prefix_len(char *word)
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

int	expand_tilde(char **word)
{
	int		i;
	char	*t_prefix;
	char	*value;
	char	*tmp;

	value = NULL;
	i = tilde_prefix_len((*word));
	if ((t_prefix = ft_strsub((*word), 0, i)) != NULL)
	{
		if ((value = get_value(t_prefix)) != NULL)
		{
			if ((tmp = ft_strjoin(value, &(*word)[i])) != NULL)
			{
				free(*word);
				(*word) = tmp;
			}
		}
		free (t_prefix);
	}
	return EXIT_SUCCESS;
}

int expand_assignments(char **assignment)
{
	int i;
	char *name;
	char *tmp;
	char *final;
	char **variables; // free

	i = 0;
	tmp = NULL;
	final = NULL;
	while ((*assignment)[i] != '\0' && (*assignment)[i] != '=')
		i++;
	name = ft_strsub((*assignment), 0, i + 1);
	variables = ft_strsplit(&(*assignment)[i + 1], ':');
	i = 0;
	while (variables[i] != NULL)
	{
		if (variables[i][0] == '~')
			expand_tilde(&variables[i]);
		if (i == 0)
			final = ft_strjoin(name, variables[i]);
		else
		{
			tmp = ft_strjoin(":", variables[i]);
			final = ft_strjoin(final, tmp);
			free(tmp);
		}
		i++;
	}
	free((*assignment));
	(*assignment) = final;
	return EXIT_SUCCESS;
}

int tilde_expansion(t_process *p)
{
	int i;
	int status;

	i = 0;
	status = 0;
	while (p->av[i] != NULL)
	{
		if (p->av[i][0] == '~')
		{
			status = expand_tilde(&p->av[i]);
		}
		if (ft_strchr(p->av[i], '=') != NULL)
		{
			status = expand_assignments(&p->av[i]);
		}
		i++;
	}
	return (status);
}