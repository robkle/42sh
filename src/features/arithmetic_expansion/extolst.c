#include "shell.h"

int	ft_operator(char c)
{
	char *ops;

	ops = "+-*/%()<>!=&|";
	if (ft_strchr(ops, c))
		return (1);
	return (0);
}

static void	ft_op_parse(char *exp, int *i, char op[])
{
	if (exp[*i] == '+' || exp[*i] == '-')
	{
		while (exp[*i] == '+' || exp[*i] == '-')
		{	
			ft_strncat(op, &exp[*i], 1);
			*i += 1;
		}
		*i -= 1;
	}
	else if ((exp[*i] == '<' || exp[*i] == '>' || \
	exp[*i] == '=' || exp[*i] == '!') && exp[*i + 1] == '=')
	{
		ft_strncpy(op, &exp[*i], 2);
		*i += 1;
	}
	else if ((exp[*i] == '&' || exp[*i] == '|') && exp[*i + 1] == exp[*i])
	{
		ft_strncpy(op, &exp[*i], 2);
		*i += 1;
	}
	else
		op[0] = exp[*i];
}

static void	ft_write_to_lst(t_st **infix, char arr[])
{
	ft_push_lst(infix, arr, NULL);
	ft_bzero(arr, ft_strlen(arr));
}

t_st	*ft_extolst(char *exp)
{
	t_st	*infix;
	char	buf[13];
	char	op[64];
	int		i;

	infix = NULL;
	ft_bzero(buf, 13);
	ft_bzero(op, 64);
	i = -1;
	while (exp[++i])
	{
		if (ft_operator(exp[i]))
			ft_op_parse(exp, &i, op);
		else if (ft_isalnum(exp[i]) || exp[i] == '_' || exp[i] == '#' || \
		exp[i] == '@')
			ft_strncat(buf, &exp[i], 1);
		else
			ft_strncat(op, &exp[i], 1);
		if (op[0])
			ft_write_to_lst(&infix, op);
		if (buf[0] && !(ft_isalnum(exp[i + 1]) || exp [i + 1] == '_' || \
		exp[i + 1] == '#' || exp[i + 1] == '@'))
			ft_write_to_lst(&infix, buf);
	}
	return (ft_infix_checker(infix));
}
