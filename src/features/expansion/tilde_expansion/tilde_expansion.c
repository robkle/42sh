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

char	*get_specified_login_value(char *t_prefix, char *home, char *logname,
int i)
{
	int			j;
	char		*value;
	char		*homedir;
	struct stat	sb;

	j = 0;
	value = NULL;
	while (home[i] != '\0')
	{
		j = 0;
		while (logname[j] == home[i + j])
		{
			if (logname[j + 1] == '\0')
			{
				homedir = ft_strsub(home, 0, i);
				value = ft_strjoin(homedir, t_prefix);
				free(homedir);
				if (stat(value, &sb) == -1)
				{
					free(value);
					return (NULL);
				}
			}
			j++;
		}
		i++;
	}
	return (value);
}

char	*get_login_value(char *t_prefix)
{
	char	*home;
	char	*logname;
	int		i;

	i = 0;
	if (ft_strcmp(t_prefix, "root") == 0)
		return (ft_strdup("/var/root"));
	if ((home = ft_getenv("HOME")) == NULL)
		return (NULL);
	if ((logname = ft_getenv("LOGNAME")) == NULL)
		return (NULL);
	return (get_specified_login_value(t_prefix, home, logname, i));
}

char	*get_value(char *t_prefix)
{
	char *value;

	if ((ft_strcmp(t_prefix, "~/") == 0 || ft_strcmp(t_prefix, "~") == 0) &&
		(value = ft_getenv("HOME")) != NULL)
		return (ft_strdup(value));
	else if (ft_strcmp(&t_prefix[1], (value = ft_getenv("LOGNAME"))) == 0)
	{
		if ((value = ft_getenv("HOME")) != NULL)
			return (ft_strdup(value));
	}
	else if (ft_strcmp(t_prefix, "~+") == 0 &&
		(value = ft_getenv("PWD")) != NULL)
		return (ft_strdup(value));
	else if (ft_strcmp(t_prefix, "~-") == 0 &&
		(value = ft_getenv("OLDPWD")) != NULL)
		return (ft_strdup(value));
	return (value = get_login_value(&t_prefix[1]));
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

int		expand_tilde(char **word)
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
			free(value);
		}
		free(t_prefix);
	}
	return (EXIT_SUCCESS);
}

void	expand_assignment_variables(char **final, char ***variables, char *name)
{
	int		i;
	char	*tmp;

	i = 0;
	tmp = NULL;
	while ((*variables)[i] != NULL)
	{
		if ((*variables)[i][0] == '~')
			expand_tilde(&(*variables)[i]);
		if (i == 0)
			(*final) = ft_strjoin(name, (*variables)[i]);
		else
		{
			tmp = ft_strjoin(":", (*variables)[i]);
			(*final) = ft_strjoin((*final), tmp);
			free(tmp);
		}
		i++;
	}
}

int		expand_assignments(char **assignment)
{
	int		i;
	char	*name;
	char	*final;
	char	**variables;

	i = 0;
	final = NULL;
	while ((*assignment)[i] != '\0' && (*assignment)[i] != '=')
		i++;
	name = ft_strsub((*assignment), 0, i + 1);
	variables = ft_strsplit(&(*assignment)[i + 1], ':');
	i = 0;
	expand_assignment_variables(&final, &variables, name);
	destroy_arr(variables);
	free(name);
	free((*assignment));
	(*assignment) = final;
	return (EXIT_SUCCESS);
}

int		tilde_expansion(t_process *p)
{
	int		i;
	int		status;
	t_redi	*tmp;

	i = 0;
	status = 0;
	tmp = p->first_redi;
	while (p->av[i] != NULL)
	{
		if (p->av[i][0] == '~')
			status = expand_tilde(&p->av[i]);
		if (ft_strchr(p->av[i], '=') != NULL)
			status = expand_assignments(&p->av[i]);
		i++;
	}
	while (tmp != NULL)
	{
		if (tmp->word != NULL && tmp->word[0] == '~')
			status = expand_tilde(&tmp->word);
		tmp = tmp->next;
	}
	return (status);
}
