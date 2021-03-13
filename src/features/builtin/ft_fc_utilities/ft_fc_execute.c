/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fc_execute.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthan <dthan@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/13 22:20:16 by dthan             #+#    #+#             */
/*   Updated: 2021/03/13 22:49:20 by dthan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static t_token	*tokenizing_service_fc(char *first_str)
{
	t_tokennizing_service instance;

	init_token_service_struct(&instance);
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

static void		ft_fc_execute_clean_up(t_token *tk_lst, t_astnode *ast)
{
	if (tk_lst)
		clear_token(tk_lst);
	if (ast)
		clear_ast(ast);
}

void			ft_fc_execute(char *cmd)
{
	t_token		*tk_lst;
	t_astnode	*ast;

	tk_lst = NULL;
	ast = NULL;
	if (ft_fc_get_user_token(&tk_lst, cmd) == EXIT_FAILURE)
		return (ft_fc_execute_clean_up(tk_lst, ast));
	print_token(tk_lst);
	if ((ast = semantic_analysis(tk_lst)) == NULL)
		return (ft_fc_execute_clean_up(tk_lst, ast));
	if (find_heredoc(ast) == EXIT_FAILURE)
		return (ft_fc_execute_clean_up(tk_lst, ast));
	executor(ast);
	return (ft_fc_execute_clean_up(tk_lst, ast));
}
