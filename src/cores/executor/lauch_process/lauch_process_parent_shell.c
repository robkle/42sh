/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lauch_process_parent_shell.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthan <dthan@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/28 03:49:44 by dthan             #+#    #+#             */
/*   Updated: 2021/03/14 14:46:52 by dthan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static int	lauch_process_which_can_change_shell2(t_process *p)
{
	if (ft_strequ(p->av[0], "jobs"))
		return (ft_jobs(p));
	else if (ft_strequ(p->av[0], "fc"))
		return (ft_fc(p));
	else if (ft_strequ(p->av[0], "export"))
		return (ft_export(p->ac, p->av));
	else if (ft_strequ(p->av[0], "set"))
		return (ft_set());
	else if (ft_strequ(p->av[0], "unset"))
		return (ft_unset(p->ac, p->av));
	else if (ft_strequ(p->av[0], "hash"))
		return (ft_hash(p));
	else if (ft_strequ(p->av[0], "type"))
		return (ft_type(p));
	else if (ft_strequ(p->av[0], "pwd"))
		return (ft_pwd(p));
	return (EXIT_FAILURE);
}

static int	lauch_process_which_can_change_shell(t_process *p)
{
	if (ft_strequ(p->av[0], "exit"))
		return (ft_exit(p));
	else if (ft_strequ(p->av[0], "alias"))
		return (ft_alias(p));
	else if (ft_strequ(p->av[0], "unalias"))
		return (ft_unalias(p));
	else if (ft_strequ(p->av[0], "cd"))
		return (ft_cd(p));
	else if (ft_strequ(p->av[0], "setenv"))
		return (ft_setenv(p));
	else if (ft_strequ(p->av[0], "unsetenv"))
		return (ft_unsetenv(p));
	else if (ft_strequ(p->av[0], "fg"))
		return (ft_fg(p));
	else if (ft_strequ(p->av[0], "bg"))
		return (ft_bg(p));
	else if (ft_strequ(p->av[0], "echo"))
		return (ft_echo(p));
	return (lauch_process_which_can_change_shell2(p));
}

static int	lauch_assignment_words(t_assignment *list)
{
	t_var			*intern_var;
	t_var			*ptr_var;
	t_assignment	*ptr;

	ptr = list;
	while (ptr)
	{
		intern_var = (t_var*)ft_memalloc(sizeof(t_var));
		intern_var->name =
			ft_strndup(ptr->data, ft_strchr(ptr->data, '=') - &ptr->data[0]);
		intern_var->value = ft_strdup(ft_strchr(ptr->data, '=') + 1);
		if (ft_getenv(intern_var->name) || ft_strequ(intern_var->name, "PATH"))
			intern_var->exported = 1;
		else if ((ptr_var = ft_getvar(intern_var->name)) != NULL &&
			ptr_var->exported == 1)
			intern_var->exported = 1;
		else
			intern_var->exported = 0;
		(is_intern_var(intern_var->name)) ? update_intern_var(intern_var) :
			add_intern_var(intern_var);
		ptr = ptr->next;
	}
	return (EXIT_SUCCESS);
}

int			lauch_in_parent_process(t_process *p)
{
	if (handle_redirection(p) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (p->av[0])
		return (lauch_process_which_can_change_shell(p));
	return (lauch_assignment_words(p->first_assignment));
}
