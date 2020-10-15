#include "shell.h"

static int		ft_fc_flags(char *str, int *flags)
{
	int i;
	
	if (str[1] == 'e' && !str[2] && *flags == 0)
	{
		*flags = !(*flags & 16) ? *flags + 16 : *flags;
		return (1);
	}
	i = 0;
	while (str[++i])
	{
		if (str[i] == 'l')
			*flags = !(*flags & 1) ? *flags + 1 : *flags;
		else if (str[i] == 'n')
			*flags = !(*flags & 2) ? *flags + 2 : *flags;
		else if (str[i] == 'r')
			*flags = !(*flags & 4) ? *flags + 4 : *flags;
		else if (str[i] == 's')
			*flags = !(*flags & 8) ? *flags + 8 : *flags;
		else
		{
			ft_printf("fc: -%c: invalid option\n", str[i]);
			return (0);
		}
	}
	return (1);
}
	
static int		ft_fc_options(t_process *p, int *flags, char **ed, char **range)
{
	int	i;

	i = 1;
	while (i < p->ac && p->av[i][0] == '-' && p->av[i][1])
	{
		if (!ft_fc_flags(p->av[i], flags))
			return (0);
		else if (*flags == 16)
		{
			*flags = 0;
			bzero(*ed, 16);
			ft_strcpy(*ed, p->av[++i]);
		}
		i++;
	}
	//check option pat=rep for -s flag
	range[0] = i < p->ac ? ft_strdup(p->av[i++]) : NULL;
	range[1] = i < p->ac ? ft_strdup(p->av[i]) : NULL;
	range[2] = NULL;
	return (1);
}

static int	ft_fc_process(int flags, /*char *ed,*/ char **range)
{
	if (flags < 8 && flags % 2)
	{
		if (!ft_fc_list(flags, range))
		{
			//error message
			return (0);	
		}
	}
/*	else
	{
		if (!ft_fc_exec(flags, range, ed))
		{
			//error message
			return (0);
		}
	}*/ //commented out until ft is written
	return (1);
}

int		ft_fc(t_process *p)
{
	int		flags;
	char	*ed;
	char	**range;
	
	flags = 0;
	ed = ft_memalloc(16);
	ft_strcpy(ed, "vim");
	range = (char **)malloc(sizeof(char*) * 3);
	if (!ft_fc_options(p, &flags, &ed, range))
	{
		//error message
		return (EXIT_FAILURE);
	}
	if (!ft_fc_process(flags/*, ed*/, range))
	{
		//error message
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
