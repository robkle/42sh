/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fc_execute.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthan <dthan@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/13 22:20:16 by dthan             #+#    #+#             */
/*   Updated: 2021/03/19 19:20:01 by dthan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static t_token	*tokenizing_service_fc(char *first_str)
{
	t_tokennizing_service instance;

	init_tokenizing_service_struct(&instance);
	instance.single_cmd = ft_strdup(first_str);
	tokenizing_service_helper(&instance);
	while (instance.lex_value != LEX_SUCCESS &&
		instance.lex_value != LEX_FAILURE)
	{
		if ((instance.single_cmd = get_command(instance.lex_value)) == NULL)
		{
			(instance.token_stream) ? clear_token(instance.token_stream) : 0;
			instance.token_stream = NULL;
			break ;
		}
		tokenizing_service_helper(&instance);
	}
	(instance.whole_cmd) ? free(instance.whole_cmd) : 0;
	return (instance.token_stream);
}

static int		ft_fc_get_user_token(t_token **tk_lst, char *first_str)
{
	*tk_lst = tokenizing_service_fc(first_str);
	if (*tk_lst == NULL)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

static void		init_ft_fc_execute_service(t_ft_fc_excecute_service *self)
{
	self->tk_lst = NULL;
	self->ast = NULL;
	self->shell_first_heredoc = g_shell.first_heredoc;
	self->shell_heredoc_lst = g_shell.heredoc_lst;
	g_shell.first_heredoc = NULL;
	g_shell.heredoc_lst = NULL;
}

static void		destroy_ft_fc_execute_service(t_ft_fc_excecute_service self)
{
	(self.tk_lst) ? clear_token(self.tk_lst) : 0;
	(self.ast) ? clear_ast(self.ast) : 0;
	(g_shell.heredoc_lst) ? clear_heredoc(g_shell.heredoc_lst) : 0;
	g_shell.first_heredoc = self.shell_first_heredoc;
	g_shell.heredoc_lst = self.shell_heredoc_lst;
}

void			ft_fc_execute(char *cmd)
{
	t_ft_fc_excecute_service instance;

	init_ft_fc_execute_service(&instance);
	if (ft_fc_get_user_token(&(instance.tk_lst), cmd) == EXIT_FAILURE)
		return (destroy_ft_fc_execute_service(instance));
	if ((instance.ast = semantic_analysis(instance.tk_lst)) == NULL)
		return (destroy_ft_fc_execute_service(instance));
	if (find_heredoc(instance.ast) == EXIT_FAILURE)
		return (destroy_ft_fc_execute_service(instance));
	g_shell.first_heredoc = g_shell.heredoc_lst;
	execute_complete_command(instance.ast);
	destroy_ft_fc_execute_service(instance);
}
