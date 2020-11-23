/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthan <dthan@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/26 20:14:36 by ihwang            #+#    #+#             */
/*   Updated: 2020/10/29 15:17:00 by dthan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static char		**set_env(char **sample)
{
	char	**env;
	int		i;

	i = -1;
	while (sample[++i])
		NULL;
	env = (char**)malloc(sizeof(char*) * (i + 1));
	i = -1;
	while (sample[++i])
	{
		env[i] = (char*)malloc(sizeof(char) * PATH_MAX);
		ft_strcpy(env[i], sample[i]);
	}
	env[i] = NULL;
	return (env);
}

static void		ft_execute(char *input)
{
	t_token		*token_lst;
	t_astnode	*ast;

	ast = NULL;
	input = ft_strjoin_and_free_string1(input, "\n");
	if ((token_lst = lexer_and_parser(input)) != NULL)
	{
		if ((ast = syntax_analysis(token_lst)) != NULL)
			executor(ast);
		clear_token(token_lst);
	}
	ft_strdel(&input);
}

static char		*get_input(int level, int count_pmpt, char *quote)
{
	t_l			l;

	ft_memset(&l, 0, sizeof(t_l));
	if (level != 1)
		l.type = LINE_TYPE_DQUOTE;
	l.pmpt = count_pmpt;
	ft_get_line(&l, &g_h);
	if (is_open_dquote(l.line, level, quote))
	{
		ft_putstr("dquote> ");
		l.line = ft_strjoin_and_free_string1(l.line, "\n");
		l.line = 
			ft_strjoin_and_free_string2(l.line, get_input((int)2, 8, quote));
	}
	return (l.line);
}

static int		shell(void)
{
	char *line;
	char quote;

	get_history(&g_h, 0);
	while (1)
	{
		do_job_notification();
		if (!g_prompt)
			get_prompt();
		g_status = 0;
		quote = '\0';
		line = get_input(1, 2, &quote);
		// get_next_line(STDOUT_FILENO, &line);
		if (!iseof_in_line(line))
			// ft_execute(&line);
			ft_execute(line);
	}
	return (0);
}

int				init_shell(void)
{
	if (!isatty(STDIN_FILENO))
	{
		//Todo define macros for errno No.5 and NO.25
		return (0);
	}
	if (!(getenv("TERM")))
	{
		ft_putstr_fd("Environment variable 'TERM' not set\n", 2);
		return (0);
	}
	sig_controller(PARENT);
	g_shell.shell_pgid = getpgrp();
	if (setpgid(g_shell.shell_pgid, g_shell.shell_pgid) == -1)
		return (0);
	ft_tcsetpgrp(STDIN_FILENO, g_shell.shell_pgid);
	tcgetattr(STDIN_FILENO, &g_shell.shell_tmode);
	return (1);
}

/* working
int				init_shell(void)
{
	g_shell.shell_terminal = STDIN_FILENO;
	g_shell.interactive_shell = isatty(STDIN_FILENO);
	if (g_shell.interactive_shell);
	{
		while (ft_tcgetpgrp(g_shell.shell_terminal) != \
				(g_shell.shell_pgid = getpgrp()))
			kill (-g_shell.shell_pgid, SIGTTIN);
	}




	if (!isatty(STDIN_FILENO))
	{
		//Todo define macros for errno No.5 and NO.25
		return (0);
	}
	if (!(getenv("TERM")))
	{
		ft_putstr_fd("Environment variable 'TERM' not set\n", 2);
		return (0);
	}
	sig_controller(PARENT);
	g_shell.shell_pgid = getpgrp();
	if (setpgid(g_shell.shell_pgid, g_shell.shell_pgid) == -1)
		return (0);
	ft_tcsetpgrp(STDIN_FILENO, g_shell.shell_pgid);
	tcgetattr(STDIN_FILENO, &g_shell.shell_tmode);
	return (1);
}
*/

int				main(int ac, char **av, char **envp)
{
	(void)ac;
	(void)av;
	g_env = set_env(envp);
	g_alias = (t_alias**)malloc(sizeof(t_alias*) + 1);
	g_alias[0] = NULL;
	if (!init_shell())
		ft_exit(EXIT_FAILURE);
	increment_shlvl();
	return (shell());
}
