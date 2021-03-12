/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthan <dthan@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/26 20:14:36 by ihwang            #+#    #+#             */
/*   Updated: 2021/03/12 22:11:08 by dthan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

/*
** function get_command
**	@phase : the starting phase of the editing
*/

void reset_value(t_token **tk_lst, t_astnode **ast)
{
	(*tk_lst != NULL) ? clear_token((*tk_lst)) : 0;
	(*ast != NULL) ? clear_ast(*ast) : 0;
	(g_shell.heredoc_lst != NULL) ? clear_heredoc(g_shell.heredoc_lst) : 0;
	append_history();
	(g_shell.history->tmp != NULL) ? free(g_shell.history->tmp) : 0;
	*tk_lst = NULL;
	*ast = NULL;
	g_shell.heredoc_lst = NULL;
	g_shell.first_heredoc = NULL;
	g_shell.history->tmp = NULL;
	g_shell.signal_indicator = 0;
}

static int		shell(void)
{
	t_token *tk_lst;
	t_astnode *ast;

	tk_lst = NULL;
	ast = NULL;
	while ("shell is interactive")
	{
		reset_value(&tk_lst, &ast);
		do_job_notification();
		print_info();
		if ((tk_lst = tokenizing_service()) == NULL)
			continue ;
		print_token(tk_lst);
		if ((ast = semantic_analysis(tk_lst)) == NULL)
			continue ;
		if (find_heredoc(ast) == EXIT_FAILURE)
			continue ;
		g_shell.first_heredoc = g_shell.heredoc_lst;
		printBinaryTree(ast);
		executor(ast);
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
	/*
	** init environment variable
	*/
	g_shell.env = set_env(envp);
	g_shell.intern_var = set_var(envp);
	if (!(ft_getenv("TERM")))
	{
		ft_putstr_fd("Environment variable 'TERM' not set\n", 2);
		return (EXIT_FAILURE);
	}
	/* signal */
	sig_controller(PARENT);
	init_signal_messages();
	/* job control */
	g_shell.shell_pgid = getpgrp();
	if (setpgid(g_shell.shell_pgid, g_shell.shell_pgid) == -1)
		return (EXIT_FAILURE);
	ft_tcsetpgrp(STDIN_FILENO, g_shell.shell_pgid);
	tcgetattr(STDIN_FILENO, &g_shell.shell_tmode);
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
	g_shell.alias = NULL;
	/*
	** init hash
	*/
	//g_shell.hashtable = (t_hash**)malloc(MAX_HASH * sizeof(t_hash*) + 1);
	//g_shell.hashtable[MAX_HASH] = NULL;
	/*
	** promp stuff here
	*/
	g_shell.signal_indicator = 0;
	/*
	** heredoc stuff
	*/
	g_shell.first_heredoc = NULL;
	g_shell.heredoc_lst = NULL;
	/*
	** exit status
	*/
	g_shell.exit_status = 1;
	/*
	**	init builtin commands list for 'type' command
	**	Could be used for shortening some functions such as is_builtin()
	**	or exec_builtin() in lauch_proces_child_shell.c
	*/
	g_shell.builtins = set_builtin_commands();
	return (EXIT_SUCCESS);
}

int				main(int ac, char **av, char **envp)
{
	(void)ac;
	(void)av;
	if (init_shell(envp) == EXIT_FAILURE)
		ft_exit_internal(EXIT_FAILURE);
	increment_shlvl();
	return (shell());
}
