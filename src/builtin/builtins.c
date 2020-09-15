/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihwang <ihwang@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/06 15:27:24 by ihwang            #+#    #+#             */
/*   Updated: 2020/09/15 21:05:20 by ihwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

char		*bascket[200];

void		combine_two_sorted_arrays(void)
{
	int		env;
	int		var;
	int		pos_bascket;

	env = 0;
	var = 0;
	pos_bascket = 0;
	while ((g_env[env] && g_env[env][0] != '\0') && \
			(g_var && g_var[var] && g_var[var][0] != '\0'))
	{
		if (ft_strcmp(g_env[env], g_var[var]) <= 0)
			bascket[pos_bascket] = g_env[env++];
		else if (ft_strcmp(g_env[env], g_var[var]) >0 )
			bascket[pos_bascket] = g_var[var++];
		++pos_bascket;
	}
	while (g_env[env] && g_env[env][0] != '\0')
		bascket[pos_bascket++] = g_env[env++];
	while (g_var && g_var[var] && g_var[var][0] != '\0')
		bascket[pos_bascket++] = g_var[var++];
	bascket[pos_bascket] = NULL;
}

void		merge(char **arr, int low, int mid, int high)
{
	int		left;
	int		right;
	int		index;

	index = 0;
	left = low;
	right = mid + 1;
	while (left <= mid && right <= high)
	{
		if (ft_strcmp(arr[left], arr[right]) <= 0)
			bascket[index++] = arr[left++];
		else if (ft_strcmp(arr[left], arr[right]) > 0)
			bascket[index++] = arr[right++];
	}
	while (left <= mid)
		bascket[index++] = arr[left++];
	while (right <= high)
		bascket[index++] = arr[right++];
	--index;
	while (index >= 0)
	{
		arr[low + index] = bascket[index];
		--index;
	}
}

void		merge_sort(char **arr, int low, int high)
{
	int		mid;

	if (low < high)
	{
		mid = (low + high) / 2;
		merge_sort(arr, low, mid);
		merge_sort(arr, mid + 1, high);
		merge(arr, low, mid, high);
	}
	else
		return ;
}

int         ft_set(void)
{
	int		env_len;
	int		var_len;
	int		index;

	env_len = 0;
	while (g_env[env_len])
		++env_len;
	merge_sort(g_env, 0, env_len - 1);
	var_len = 0;
	if (g_var && g_var[var_len] && g_var[0][0] != '\0')
	{
		while (g_var[var_len] && g_var[var_len][0] != '\0')
			++var_len;
		merge_sort(g_var, 0, var_len - 1);
	}
	combine_two_sorted_arrays();
	index = 0;
	while (bascket[index])
	{
		ft_putstr(bascket[index++]);
		ft_putchar('\n');
	}
	return (EXIT_SUCCESS);
}

int			check_export_syntax(char *data)
{
	int		i;

	i = -1;
	while (data[++i])
		if (!ft_isalnum(data[i]) && data[i] != '=')
			return (false);
	if (!ft_isalpha(data[0]))
		return (false);
	return (true);
}

static void	unset_var(char *input, char *var)
{
	t_exe	temp_cmd[1];

	g_env = add_env(input, g_env);
	temp_cmd->ac = 2;
	temp_cmd->av = malloc(sizeof(char*) * 2);
	temp_cmd->av[0] = ft_strdup("temp_unset");
	temp_cmd->av[1] = ft_strndup(var, (int)(ft_strchr(var, '=') - var));
	free(ft_unset((t_exe*)temp_cmd, &g_var));
	ft_strlst_del(&temp_cmd->av, 2);
}

static int	get_len_split(char **split)
{
	int		i;

	i = 0;
	while (split[i])
		i++;
	return (i);
}

void		execute_export(char *data)
{
	int		i;
	char	*var;
	char	**split;

	split = ft_strsplit(data, '=');
	if ((var = get_var(split[0], g_env, VAL)))
	{
		i = 1;
		*var = '\0';
		while (split[i])
		{
			ft_strcat(var, split[i]);
			if (split[++i])
				ft_strcat(var, "=");
		}
	}
	else if (g_var && (var = get_var(split[0], g_var, KEY)) && \
				!ft_strchr(data, '='))
		unset_var(var, var);
	else if (g_var && var && ft_strchr(data, '='))
		unset_var(data, var);
	else
		g_env = add_env(data, g_env);
	ft_strlst_del(&split, get_len_split(split));
}

char		*ft_export(t_exe *c)
{
	int		i;
	char	*ret;

	if (c->ac == 1)
		return (ft_strdup("ft_env"));
	i = 0;
	ret = ft_strdup("success");
	while (++i < c->ac)
	{
		if (!check_export_syntax(c->av[i]))
		{
			if (ft_strequ(ret, "success"))
			{
				ft_strdel(&ret);
				ret = ft_strdup("42sh: export: `");
			}
			else
				ret = ft_strjoin(ret, "\n42sh: export: `");
			ret = ft_strjoin(ret, c->av[i]);
			ret = ft_strjoin(ret, "\': not a valid identifier\n");
		}
		else
			execute_export(c->av[i]);
	}
	return (ret);
}

int			ft_env(void)
{
	int		i;

	i = -1;
	while (g_env[++i])
	{
		ft_putstr(g_env[i]);
		ft_putstr("\n");
	}
	return (EXIT_SUCCESS);
}

int			ft_pwd(void)
{
	char	pwd[PATH_MAX];

	if ((getcwd(pwd, PATH_MAX)) == NULL)
		return (EXIT_FAILURE);
	ft_putstr(pwd);
	ft_putstr("\n");
	return (EXIT_SUCCESS);
}

int			ft_exit(int opt)
{
	int		i;

	i = -1;
	delete_save_history(&g_h);
	while (g_env[++i])
		ft_strdel(&g_env[i]);
	ft_strdel(&g_env[i]);
	free(g_env);
	exit(opt);
	return (EXIT_FAILURE);
}

int			ft_echo(t_exe *c)
{
	int		i;

	i = 0;
	while (++i < c->ac)
	{
		ft_putstr(c->av[i]);
		if (i + 1 != c->ac && ft_strcmp(c->av[i], ""))
			ft_putstr(" ");
	}
	ft_putchar('\n');
	return (EXIT_SUCCESS);
}
