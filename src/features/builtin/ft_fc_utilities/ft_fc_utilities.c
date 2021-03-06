/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fc_utilities.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthan <dthan@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/19 17:55:41 by dthan             #+#    #+#             */
/*   Updated: 2021/03/06 16:32:50 by dthan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int		ft_num_check(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '-')
		i++;
	while(str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

/*
** function fc_find_existing_cmd: find the command in the history list based on
** the string input
** RETURN:  return i > 0 on success
**			return 0 on error, when no matches in the history
*/

static int fc_find_existing_cmd(char *s)
{
	int i;

	i = g_shell.history->curr;
	while (i > 0)
	{
		if (ft_strnequ(s, g_shell.history->hist[i], ft_strlen(s)))
			return (i);
		i--;
	}
	return (0);
}

/*
** funtion fc_range: find the command in the history, if number is not recognized
** then it will look for the lastest command in the history list
**		PARAM:
**				@ str: the string input
**		RETURN: the position of the command acording to the its postion in the
**				history list
**				Error = 0, if the command not found
*/

int fc_range(char *str)
{
	int pos;

	if (str)
	{
		if (ft_isdigit(str[0]) || (str[0] == '-' && str[1] && ft_isdigit(str[1])))
			pos = ft_atoi(str);
		else
			return (fc_find_existing_cmd(str));
		if (pos > g_shell.history->curr || pos == 0)
			pos = g_shell.history->curr;
		else if (pos < 0)
		{
			pos = g_shell.history->curr + 1 + pos;
			if (pos < 0)
				pos = 1;
		}
	}
	else
		pos = g_shell.history->curr;
	return (pos);
}

int fc_error_history_specification_out_of_range(void)
{
	ft_dprintf(2, "%s: fc: history specification out of range", SHELL_NAME);
	return (EXIT_FAILURE);
}

int fc_error_no_command_found(void)
{
	ft_dprintf(2, "%s: fc: no command found\n", SHELL_NAME);
	return (EXIT_FAILURE);
}

void fc_cleanup(char *editor, char **block)
{
	if (editor)
		free(editor);
	if (block[FIRST])
		free(block[FIRST]);
	if (block[LAST])
		free(block[LAST]);
	if (block[REPLACE])
		free(block[REPLACE]);
}

// int ft_fc_get_user_token(t_token **tk_lst, char *first_str)
// {
// 	char *whole_cmd;
// 	char *cmd;
// 	int ret;
// 	t_lex_value lex_value;

// 	whole_cmd = NULL;
// 	ret = EXIT_SUCCESS;
// 	lex_value = LEX_CMD;
// 	cmd = ft_strdup(first_str);
// 	while ("user is editing")
// 	{
// 		lex_value = lexical_analysis_and_syntax_analysis(cmd, tk_lst, lex_value, 0);
// 		if (lex_value == LEX_FAILURE || ft_strequ(cmd, ENTER_KEY))
// 			free(cmd);
// 		else
// 			whole_cmd = ft_strjoin_and_free_2strings(whole_cmd, cmd);
// 		if (lex_value == LEX_SUCCESS || lex_value == LEX_FAILURE)
// 		{
// 			ret = lex_value;
// 			break ;
// 		}
// 		if ((cmd = get_command(lex_value)) == NULL)
// 		{
// 			ret = EXIT_FAILURE;
// 			break ;
// 		}
// 	}
// 	if (whole_cmd)
// 	{
// 		if (g_shell.history->tmp)
// 			free(g_shell.history->tmp);
// 		g_shell.history->tmp = whole_cmd;
// 	}
// 	return (ret);
// }

t_token *tokenizing_service_fc(char *first_str)
{
	t_tokennizing_service instance;

	init_token_service_struct(&instance);
	instance.single_cmd = first_str;
	while (instance.lex_value != LEX_SUCCESS && instance.lex_value != LEX_FAILURE)
	{
		instance.lex_value = lexical_and_syntax_analysis(instance.lex_value, instance.single_cmd, &(instance.token_stream));
		if (instance.lex_value != LEX_FAILURE)
			instance.whole_cmd = ft_strjoin_and_free_2strings(instance.whole_cmd, instance.single_cmd);
		else
			free(instance.single_cmd);
		if ((instance.single_cmd = get_command(instance.lex_value)) == NULL)
		{
			(instance.token_stream) ? clear_token(instance.token_stream) : 0;
			instance.token_stream = NULL;
			break ;
		}
	}
	if (instance.whole_cmd)
		g_shell.history->tmp = instance.whole_cmd;
	return (instance.token_stream);
}

int ft_fc_get_user_token(t_token **tk_lst, char *first_str)
{
	*tk_lst = tokenizing_service_fc(first_str);
	if (*tk_lst == NULL)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}


void ft_fc_execute_clean_up(t_token *tk_lst, t_astnode *ast)
{
	if (tk_lst)
		clear_token(tk_lst);
	if (ast)
		clear_ast(ast);
}

void ft_fc_execute(char *cmd)
{
	t_token *tk_lst;
	t_astnode *ast;

	tk_lst = NULL;
	ast = NULL;
	if (ft_fc_get_user_token(&tk_lst, cmd) == EXIT_FAILURE)
		return (ft_fc_execute_clean_up(tk_lst, ast));
	print_token(tk_lst);
	if ((ast = semantic_analysis(tk_lst)) == NULL)
		return (ft_fc_execute_clean_up(tk_lst, ast));
	// if (find_heredoc(ast) == EXIT_FAILURE)
		// continue ;
	executor(ast);
	return (ft_fc_execute_clean_up(tk_lst, ast));
}
