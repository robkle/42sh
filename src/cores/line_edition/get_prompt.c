/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_prompt.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthan <dthan@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/02 15:30:45 by tango             #+#    #+#             */
/*   Updated: 2021/01/15 13:40:52 by dthan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static void	print_42sh_usr(void)
{
	char 		*usr;

	ft_putstr(PMPT_MGTA);
	ft_putstr(PMPT_BOLD);
	ft_printf("%s ", SHELL_NAME);
	ft_putstr(PMPT_INIT);
	if ((usr = ft_getenv("USER")))
	{
		ft_putstr(PMPT_SKYB);
		ft_printf(usr);
	}
	ft_printf(" ");
}

static void	print_cwd(void)
{
	char 		pwd[PATH_MAX];
	char 		*home;

	getcwd(pwd, PATH_MAX);
	ft_putstr(PMPT_YELW);
	ft_printf("[");
	if ((home = ft_getenv("HOME")))
	{
		if (ft_strequ(pwd, home))
			ft_printf("%s", pwd);
		else if (ft_strstr(pwd, home))
		{
			ft_printf("~");
			ft_printf("%s", ft_strstr_e(pwd, home));
		}
		else
			ft_printf("%s", pwd);
	}
	else
		ft_printf("%s", pwd);
	ft_printf("]");
}

void	print_info(void)
{
	print_42sh_usr();
	print_cwd();
	ft_putstr(PMPT_INIT);
	ft_printf("[%d]", g_shell.exit_status);
	ft_putchar('\n');
}

void print_prompt(t_prompt prompt_type)
{
	if (prompt_type == PROMPT_CMD)
		ft_putstr("> ");
	else if (prompt_type == PROMPT_CMD_AND)
		ft_putstr("cmdand> ");
	else if (prompt_type == PROMPT_CMD_OR)
		ft_putstr("cmdor> ");
	else if (prompt_type == PROMPT_PIPE)
		ft_putstr("pipe> ");
	else if (prompt_type == PROMPT_HEREDOC)
		ft_putstr("heredoc> ");
	else if (prompt_type == PROMPT_DQUOTE)
		ft_putstr("dquote> ");
	else if (prompt_type == PROMPT_QUOTE)
		ft_putstr("quote> ");
	else if (prompt_type == PROMPT_BACKSLASH)
		ft_putstr("> ");
	else if (prompt_type == PROMPT_CMDSUBST)
		ft_putstr("cmdsubst> ");
	else if (prompt_type == PROMPT_BRACEPARAM)
		ft_putstr("braceparam> ");
}

int prompt_len(t_prompt prompt_type)
{
	if (prompt_type == PROMPT_CMD)
		return (ft_strlen("> "));
	else if (prompt_type == PROMPT_CMD_AND)
		return (ft_strlen("cmdand> "));
	else if (prompt_type == PROMPT_CMD_OR)
		return (ft_strlen("cmdor> "));
	else if (prompt_type == PROMPT_PIPE)
		return (ft_strlen("pipe> "));
	else if (prompt_type == PROMPT_HEREDOC)
		return (ft_strlen("heredoc >"));
	else if (prompt_type == PROMPT_DQUOTE)
		return (ft_strlen("dquote> "));
	else if (prompt_type == PROMPT_QUOTE)
		return (ft_strlen("quote> "));
	else if (prompt_type == PROMPT_BACKSLASH)
		return (ft_strlen("> "));
	else if (prompt_type == PROMPT_CMDSUBST)
		return (ft_strlen("cmdsubst> "));
	else if (prompt_type == PROMPT_BRACEPARAM)
		return (ft_strlen("braceparam> "));
	return (ft_strlen("> "));
}

t_prompt choose_prompt_type(t_lex_value lex, t_phase phase)
{
	if (lex > 1)
	{
		if (lex == LEX_CMD)
			return (PROMPT_CMD);
		else if (lex == LEX_CMDAND)
			return (PROMPT_CMD_AND);
		else if (lex == LEX_CMDOR)
			return (PROMPT_CMD_OR);
		else if (lex == LEX_PIPE)
			return (PROMPT_PIPE);
		return (PROMPT_CMD);
	}
	else
	{
		if (phase == PHASE_CMD)
			return (PROMPT_CMD);
		else if (phase == PHASE_DQUOTE)
			return (PROMPT_DQUOTE);
		else if (phase == PHASE_QUOTE)
			return (PROMPT_QUOTE);
		else if (phase == PHASE_BACKSLASH)
			return (PROMPT_BACKSLASH);
		else if (phase == PHASE_CMDSUBST)
			return (PROMPT_CMDSUBST);
		else if (phase == PHASE_BRACEPARAM)
			return (PROMPT_BRACEPARAM);
		return (PROMPT_CMD);
	}
}
