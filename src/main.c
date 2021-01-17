/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthan <dthan@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/26 20:14:36 by ihwang            #+#    #+#             */
/*   Updated: 2020/12/27 16:32:42 by dthan            ###   ########.fr       */
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

void		ft_execute(char *input)
{
	t_token		*token_lst;
	t_astnode	*ast;

	ast = NULL;
	if ((token_lst = lexer_and_parser(input)) != NULL)
	{
		if ((ast = syntax_analysis(token_lst)) != NULL)
			executor(ast);
		clear_token(token_lst);
	}
}

static char		*get_input(int level, int count_pmpt, char *quote)
{
	t_l			l;

	ft_memset(&l, 0, sizeof(t_l));
	if (level != 1)
		l.type = LINE_TYPE_DQUOTE;
	l.pmpt = count_pmpt;
	ft_get_line(&l);
	if (is_open_dquote(l.line, level, quote))
	{
		ft_putstr("dquote> ");
		l.line = ft_strjoin_and_free_string1(l.line, "\n");
		l.line = 
			ft_strjoin_and_free_2strings(l.line, get_input((int)2, 8, quote));
	}
	return (ft_process_history(&l));
}

static int		shell(void)
{
	char *line;
	char quote;

	while (1)
	{
		do_job_notification();
        if (!(g_shell.signal_indicator & SIGINT))
			get_prompt();
		//g_status = 0;
		quote = '\0';
		line = get_input(1, 2, &quote);
		line = ft_strjoin_and_free_string1(line, "\n");
		//get_next_line(STDOUT_FILENO, &line);
		if (!iseof_in_line(line))
			ft_execute(line);
		free(line);
		append_history();
	}
	return (0);
}

/* working */
/*
** @ init shell: for interactive shell only, non-interactive will be exited
**	Non-interactive shell:
** 		Todo: define macros for errno No.5 and NO.25 
*/
int				init_shell(char **envp)
{
	/*
	** init terminal stuff
	*/
	g_shell.shell_terminal = STDIN_FILENO;
	g_shell.interactive_shell = isatty(STDIN_FILENO);
	if (!g_shell.interactive_shell)
		return (EXIT_FAILURE);
	while (ft_tcgetpgrp(g_shell.shell_terminal) != \
			(g_shell.shell_pgid = getpgrp()))
		kill (-g_shell.shell_pgid, SIGTTIN);	
	if (!(getenv("TERM")))
	{
		ft_putstr_fd("Environment variable 'TERM' not set\n", 2);
		return (EXIT_FAILURE);
	}
	sig_controller(PARENT);
	g_shell.shell_pgid = getpgrp();
	if (setpgid(g_shell.shell_pgid, g_shell.shell_pgid) == -1)
		return (EXIT_FAILURE);
	ft_tcsetpgrp(STDIN_FILENO, g_shell.shell_pgid);
	tcgetattr(STDIN_FILENO, &g_shell.shell_tmode);
	/*
	** init environment variable
	*/
	g_shell.env = set_env(envp);
	/*
	** init history
	*/
	g_shell.history = (t_history*)malloc(sizeof(t_history));
	g_shell.history->hist = (char**)malloc(sizeof(char*) * (HISTFILESIZE + 2));
	g_shell.history->tmp = NULL;
	ft_bzero(g_shell.history->savedfile, 256);
	getcwd(g_shell.history->savedfile, 256);
	ft_strcat(g_shell.history->savedfile, "/.history");
	get_history(0);
	/*
	** init alias
	*/
	g_shell.alias = (t_alias**)malloc(sizeof(t_alias*) + 1);
	g_shell.alias[0] = NULL;
	g_shell.last_alias = NULL;
	/*
	** init hash
	*/
	g_shell.hashtable = (t_hash**)malloc(MAX_HASH * sizeof(t_hash*) + 1);
	g_shell.hashtable[0] = NULL;

	/*
	** promp stuff here
	*/
	g_shell.signal_indicator = 0;
	return (EXIT_SUCCESS);
}

int				main(int ac, char **av, char **envp)
{
	(void)ac;
	(void)av;
	if (init_shell(envp) == EXIT_FAILURE)
		ft_exit(EXIT_FAILURE);
	increment_shlvl();
	return (shell());
}
