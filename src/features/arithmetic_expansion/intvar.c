#include "shell.h"

/*static void	ft_arraydel(char **string_array)
{
	char *ptr;

	while (*string_array)
	{
		ptr = *string_array;
		string_array++;
		free(ptr);
	}
	ptr = *string_array;
	free(ptr);
}

static char	*ft_create_iv(char *var, int *val, char *op)
{
	char	*tmp;
	char	*new;

	tmp = ft_strjoin(var, "=");
	if (ft_strequ(op, "p++"))
		new = ft_strjoin(tmp, ft_itoa(++(*val)));
	else if (ft_strequ(op, "p--"))
		new = ft_strjoin(tmp, ft_itoa(--(*val)));
	else if (ft_strequ(op, "s++"))
		new = ft_strjoin(tmp, ft_itoa(*val + 1));
	else if (ft_strequ(op, "s--"))
		new = ft_strjoin(tmp, ft_itoa(*val - 1));
	else
		new = ft_strjoin(tmp, ft_itoa(*val));
	free(tmp);
	return (new);
}

static void	ft_set_iv(char *var, int *val, char *op)
{
	int		i;
	char	*new;
	char	**tmp;
	int		size;

	new = ft_create_iv(var, val, op);
	i = -1;
	while (g_iv[++i])
	{
		if (ft_strnequ(g_iv[i], var, ft_strlen(var)))
		{
			free(g_iv[i]);
			g_iv[i] = new;
			return;
		}
	}
	size = i + 1;
	tmp = (char**)malloc(sizeof(char*) * (size + 1));
	i = -1;
	while (++i < size - 1)
		tmp[i] = ft_strdup(g_iv[i]);
	tmp[i++] = new;
	tmp[i] = NULL;
	ft_arraydel(g_iv);
	g_iv = tmp;
}*/

/*void	ft_intvar(t_st *stack, char *op)
{
	int		i;
	int		val;
	if (!op) //Temporary to satisfy compiler for now
		return ;
	val = 0;*/
	/*i = -1;
	while (g_iv[++i])
	{
		if (ft_strnequ(g_iv[i], stack->op, ft_strlen(stack->op)))
		{
			val = ft_atoi(ft_strchr(g_iv[i], '=') + 1);
			if (op)
				ft_set_iv(stack->op, &val, op);
			ft_modify_link(stack, ft_itoa(val), "integer");	
			return ;
		}
	}
	ft_set_iv(stack->op, &val, op);*/
/*	ft_modify_link(stack, ft_itoa(val), "integer");	
}*/

static void ft_update_value(t_var *intern_var, char *op)
{
	char	*tmp;
	int		val;

	val = ft_atoi(intern_var->value);
	tmp = intern_var->value;
	if (ft_strequ(op, "p++") || ft_strequ(op, "s++"))
		intern_var->value = ft_itoa(val + 1);
	if (ft_strequ(op, "p--") || ft_strequ(op, "s--"))
		intern_var->value = ft_itoa(val - 1);
	if (tmp)
		free(tmp);
}

void	ft_intvar(t_st *stack, char *op)
{
	t_var	*tmp_var;
	t_var	*intern_var;
	int		is_var;

	intern_var = (t_var*)ft_memalloc(sizeof(t_var));
	is_var = (tmp_var = ft_getvar(stack->op)) ? 1 : 0;
	intern_var->name = is_var ? ft_strdup(tmp_var->name) : ft_strdup(stack->op);
	intern_var->value = is_var ? ft_strdup(tmp_var->value) : ft_strdup("0");
	intern_var->exported = is_var ? tmp_var->exported : 0;
	if (ft_strequ(op, "p++") || ft_strequ(op, "p--"))
		ft_update_value(intern_var, op);
	ft_modify_link(stack, intern_var->value, "integer");	
	if (ft_strequ(op, "s++") || ft_strequ(op, "s--"))
		ft_update_value(intern_var, op);
	if (is_var)
		update_intern_var(intern_var);
	else
		add_intern_var(intern_var);
}
