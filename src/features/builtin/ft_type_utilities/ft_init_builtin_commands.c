/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init_builtin_commands.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihwang <ihwang@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/03 14:35:31 by ihwang            #+#    #+#             */
/*   Updated: 2021/03/21 11:24:45 by ihwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static t_builtin	*add_node(t_builtin *head, const char *name, void *func)
{
	t_builtin		*new_head;

	new_head = (t_builtin*)malloc(sizeof(t_builtin));
	ft_bzero(new_head, sizeof(t_builtin));
	new_head->name = name;
	new_head->func = func;
	if (head == NULL)
		new_head->next = NULL;
	else
		new_head->next = head;
	return (new_head);
}

void				delete_builtin_commands(void)
{
	t_builtin		*temp;

	while (g_shell.builtins)
	{
		temp = g_shell.builtins->next;
		free(g_shell.builtins);
		g_shell.builtins = temp;
	}
}

t_builtin			*set_builtin_commands(void)
{
	t_builtin	*head;

	head = NULL;
	head = add_node(head, "exit", ft_exit);
	head = add_node(head, "alias", ft_alias);
	head = add_node(head, "unalias", ft_unalias);
	head = add_node(head, "cd", ft_cd);
	head = add_node(head, "jobs", ft_jobs);
	head = add_node(head, "fg", ft_fg);
	head = add_node(head, "bg", ft_bg);
	head = add_node(head, "fc", ft_fc);
	head = add_node(head, "echo", ft_echo);
	head = add_node(head, "set", ft_set);
	head = add_node(head, "unset", ft_unset);
	head = add_node(head, "hash", ft_hash);
	head = add_node(head, "export", ft_export);
	head = add_node(head, "type", ft_type);
	return (head);
}
