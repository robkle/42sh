/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_prompt_print.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rklein <rklein@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/19 23:26:46 by rklein            #+#    #+#             */
/*   Updated: 2021/03/19 23:28:56 by rklein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static void	print_42sh_usr(void)
{
	char	*usr;

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
	char	*pwd;
	char	*home;
	int		free_flag;

	free_flag = 0;
	pwd = NULL;
	if ((pwd = ft_getcwd_logical()) == NULL)
	{
		pwd = getcwd(NULL, 0);
		free_flag = 1;
	}
	ft_printf("%s[", PMPT_YELW);
	if ((home = ft_getenv("HOME")))
	{
		if (ft_strstr(pwd, home) && ft_strequ(pwd, home) == 0)
			ft_printf("~%s]", ft_strstr_e(pwd, home));
		else
			ft_printf("%s]", pwd);
	}
	else
		ft_printf("%s]", pwd);
	if (free_flag == 1)
		free(pwd);
}

void		print_info(void)
{
	print_42sh_usr();
	print_cwd();
	ft_putstr(PMPT_INIT);
	ft_printf("[%d]", g_shell.exit_status);
	ft_putchar('\n');
}

void		print_prompt(t_prompt prompt_type)
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
