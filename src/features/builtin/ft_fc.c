/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fc.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthan <dthan@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/20 08:49:08 by dthan             #+#    #+#             */
/*   Updated: 2021/03/19 19:17:46 by dthan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

/*
** the precedence of options in fc command if there are the apperance of all
** the options
**		-s
**		-lrn
**		-e ename / -eename
** - if there is the apperance of s option, all the other options will be
**   discarded
** - if there is the apperance of l and e, the e option will be discarded
**		note: the r and n option will be valid if there is the apperance of l
**            option
** - following the e option there will be at least 2 cases:
**		+ the next argv
**		+ after -e, there must be a name of the editor
**   otherwise there will be an error
** SYNOPSIS:
**		fc [-r] [-e editor] [first [last]]
**		fc -l [-nr] [first [last]]
**		fc -s [old=new] [first]
** OPTIONS:
**
** The fc utility shall conform to the Base Definitions volume of POSIX.1-2008,
** Section 12.2, Utility Syntax Guidelines.
**
** The following options shall be supported:
**
** -e	editor Use the editor named by editor to edit the commands. The editor
** string is a utility name, subject to search via the PATH variable (see the
** Base Definitions volume of POSIX.1-2008, Chapter 8, Environment Variables).
** The value in the FCEDIT variable  shall	be used as a default when -e is not
** specified. If FCEDIT is null or unset, ed shall be used as the editor.
**
** -l	 (The  letter  ell.) List the commands rather than invoking an editor
**       on them. The commands shall be written in the sequence indi-cated by
**       the first and last operands, as affected by -r, with each command
**       preceded by the command number.
**
** -n	 Suppress command numbers when listing with -l.
**
** -r	 Reverse the order of the commands listed (with -l) or edited (with
**       neither -l nor -s).
**
** -s	 Re-execute the command without invoking an editor.
*/

int	fc_exec(int ops, char *editor, char **block)
{
	if (ops & FC_S_OP)
		return (fc_s_op(block[REPLACE], block[FIRST]));
	return (fc_e_op(ops, editor, block[FIRST], block[LAST]));
}

int	fc_process(t_ft_fc instance)
{
	int ret;

	if (instance.ops & FC_L_OP)
		ret = fc_list(instance.ops,
			instance.blocks[FIRST],
			instance.blocks[LAST]);
	else
		ret = fc_exec(instance.ops, instance.editor, instance.blocks);
	clean_up_ft_fc_struct(instance);
	return (ret);
}

int	ft_fc(t_process *p, int foreground)
{
	t_ft_fc instance;

	if (!foreground)
	{
		ft_dprintf(2, "%s: fc: Unable to run fc in background\n",
			SHELL_NAME);
		return (EXIT_FAILURE);
	}
	if (g_shell.history->curr == 0)
	{
		ft_dprintf(2, "%s: fc: history specification out of range\n",
			SHELL_NAME);
		return (EXIT_FAILURE);
	}
	init_ft_fc_struct(&instance);
	if (fc_parse_input(p, &instance) == EXIT_FAILURE)
	{
		clean_up_ft_fc_struct(instance);
		return (EXIT_FAILURE);
	}
	return (fc_process(instance));
}
