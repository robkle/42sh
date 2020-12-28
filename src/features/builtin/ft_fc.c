/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fc.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthan <dthan@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/20 08:49:08 by dthan             #+#    #+#             */
/*   Updated: 2020/12/25 18:23:22 by dthan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int fc_is_option(char c)
{
	if (c == 'l' || c == 'n' || c == 'r' || c == 's' || c == 'e')
		return (1);
	return (0);
}

int fc_get_option(char c)
{
	if (fc_is_option(c))
	{
		if (c == 'l')
			return (FC_L_OP);
		else if (c == 'n')
			return (FC_N_OP);
		else if (c == 'r')
			return (FC_R_OP);
		else if (c == 's')
			return (FC_S_OP);
		else if (c == 'e')
			return (FC_E_OP);
	}
	return (0);
}

int fc_print_usage(void)
{
	ft_dprintf(2, "fc: usage: fc [-e ename] [-lnr] ");
	ft_dprintf(2, "[first] [last] or fc -s [pat=rep] [command]\n");
	return (EXIT_FAILURE);
}

int		fc_get_options(char *str, char *str_next, int *ops, char **editor)
{
	int i;
	int op;

	i = 0;
	while (str[++i])
	{
		op = fc_get_option(str[i]);
		if (op == 0)
		{
			ft_dprintf(2, "%s: fc: -%c: invalid option\n", SHELL_NAME, str[i]);
			return (fc_print_usage());
		}
		else if (op & FC_E_OP)
		{
			if (str_next || str[i + 1])
			{
				char *temp = *editor;
				*editor = (str[i + 1]) ? ft_strdup(&str[i + 1]) : ft_strdup(str_next);
				free(temp);
				*ops |= op;
				if (str[i + 1])
					return (EXIT_SUCCESS);
				return (2);
			}
			else
			{
				ft_dprintf(2, "%s: fc: -e: option requires an argument\n", SHELL_NAME);
				return (fc_print_usage());
			}
		}
		else
			*ops |= op;
	}
	return (EXIT_SUCCESS);
}

int fc_parse_input(t_process *p, int *ops, char **editor, char **block)
{
	int i;
	int ret;

	i = 0;
	while (p->av[++i] && p->av[i][0] == '-' && p->av[i][1])
	{
		if (ft_num_check(p->av[i])) // need to check this later
			break;
		ret = fc_get_options(p->av[i], p->av[i + 1], ops, editor);
		if (ret == EXIT_FAILURE)
			return (EXIT_FAILURE);
		else if (ret == 2)
			i++;
	}
	(i < p->ac && p->av[i] && ft_strchr(p->av[i], '=')) ? block[REPLACE] = ft_strdup(p->av[i++]) : 0;
	(i < p->ac && p->av[i]) ? block[FIRST] = ft_strdup(p->av[i++]) : 0;
	(i < p->ac && p->av[i]) ? block[LAST] = ft_strdup(p->av[i]) : 0;
	return (EXIT_SUCCESS);
}

/*
** the precedence of options in fc command if there are the apperance of all the options
**		-s
**		-lrn
**		-e ename / -eename
** - if there is the apperance of s option, all the other options will be discarded
** - if there is the apperance of l and e, the e option will be discarded
**		note: the r and n option will be valid if there is the apperance of l option
** - following the e option there will be at least 2 cases:
**		+ the next argv
**		+ after -e, there must be a name of the editor
**   otherwise there will be an error
** SYNOPSIS:
**		fc [-r] [-e editor] [first [last]]
**		fc -l [-nr] [first [last]]
**		fc -s [old=new] [first]
** OPTIONS

       The fc utility shall conform to the Base Definitions volume of POSIX.1-2008, Section 12.2, Utility Syntax Guidelines.

       The following options shall be supported:

       -e editor Use the editor named by editor to edit the commands. The editor string is a utility name, subject to search via the PATH variable
		 (see the Base Definitions volume of POSIX.1-2008, Chapter 8, Environment Variables).  The value in the FCEDIT variable  shall	be
		 used as a default when -e is not specified. If FCEDIT is null or unset, ed shall be used as the editor.

       -l	 (The  letter  ell.) List the commands rather than invoking an editor on them. The commands shall be written in the sequence indi-
		 cated by the first and last operands, as affected by -r, with each command preceded by the command number.

       -n	 Suppress command numbers when listing with -l.

       -r	 Reverse the order of the commands listed (with -l) or edited (with neither -l nor -s).

       -s	 Re-execute the command without invoking an editor.
*/

int	fc_process(int ops, char *editor, char **block)
{
	int ret;

	if (ops & FC_L_OP)
		ret = fc_list(ops, block[FIRST], block[LAST]);
	else
		ret = fc_exec(ops, editor, block);
	fc_cleanup(editor, block);
	return (ret);
}

// we can improve the default variable for default editor

int ft_fc(t_process *p)
{
	int ops;
	char *editor;
	char *block[3];

	if (g_shell.history->curr == 0)
	{
		ft_dprintf(2, "%s: fc: history specification out of range\n", SHELL_NAME);
		return EXIT_FAILURE;
	}
	ops = 0;
	editor = ft_strdup(DEFAULT_EDITOR);
	block[FIRST] = NULL;
	block[LAST] = NULL;
	block[REPLACE] = NULL;
	if (fc_parse_input(p, &ops, &editor, block) == EXIT_FAILURE)
	{
		fc_cleanup(editor, block);
		return (EXIT_FAILURE);
	}
	return (fc_process(ops, editor, block));
}
