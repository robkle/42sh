/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthan <dthan@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/26 20:14:36 by ihwang            #+#    #+#             */
/*   Updated: 2021/02/25 01:37:16 by dthan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void analyzing_phase(char *str, t_phase phase[], int *stack_pos)
{
	int i = -1;
	int len = ft_strlen(str) - 1; 

	while (++i < len)
	{
		if (phase[*stack_pos] == PHASE_BACKSLASH)
		{
			phase[(*stack_pos)--] = 0;
			continue;
		}
		if (str[i] == '"')
		{
			if (!is_quoting_phase(phase[(*stack_pos)]))
				phase[++(*stack_pos)] = PHASE_DQUOTE;
			else if (phase[*stack_pos] == PHASE_DQUOTE)
				phase[(*stack_pos)--] = 0;
		}
		else if (str[i] == '\'')
		{
			if (!is_quoting_phase(phase[(*stack_pos)]))
				phase[++(*stack_pos)] = PHASE_QUOTE;
			else if (phase[*stack_pos] == PHASE_QUOTE)
				phase[(*stack_pos)--] = 0;
		}
		else if (str[i] == '\\')
		{
			if (!is_quoting_phase(phase[(*stack_pos)]))
				phase[++(*stack_pos)] = PHASE_BACKSLASH;
		}
		else if (str[i] == '{')
		{
			if ((phase[*stack_pos] == PHASE_CMD && i > 0 && str[i - 1] == '$' && is_real_character(str, i - 1)) ||
				(phase[*stack_pos] == PHASE_BRACEPARAM && is_real_character(str, i)))
				phase[++(*stack_pos)] = PHASE_BRACEPARAM;
		}
		else if (str[i] == '(')
		{
			if ((phase[*stack_pos] == PHASE_CMD && i > 0 && str[i - 1] == '$' && is_real_character(str, i - 1)) ||
				(phase[*stack_pos] == PHASE_CMDSUBST && is_real_character(str, i)))
				phase[++(*stack_pos)] = PHASE_CMDSUBST;
		}
		else if (str[i] == '}')
		{
			if (phase[*stack_pos] == PHASE_BRACEPARAM && is_real_character(str, i))
				phase[(*stack_pos)--] = 0;
		}
		else if (str[i] == ')')
		{
			if (phase[*stack_pos] == PHASE_CMDSUBST && is_real_character(str, i))
				phase[(*stack_pos)--] = 0;
		}
	}
}

/*
** function get_command
**	@phase : the starting phase of the editing
*/

char *get_command(t_lex_value lex_value)
{
	t_phase phase[20];
	int i;
	char *cmd;
	char *line;
	t_prompt prompt_type;

	i = 0;
	cmd = ft_strnew(0);
	phase[i++] = PHASE_CMD;
	ft_bzero(phase, 20);
	prompt_type = choose_prompt_type(lex_value, 0);
	while ("command editting")
	{
		if ((line = ft_get_line(&phase[i], prompt_type, lex_value)) == NULL)
		{
			free(cmd);
			return (NULL);
		}
		if (phase[i] != PHASE_STOP)
			analyzing_phase(line, phase, &i);
		// history expansion
		if (ft_hist_exp(&line, prompt_type))
			ft_printf("%s", line);
		cmd = ft_strjoin_and_free_2strings(cmd, line);
		if (phase[i] == PHASE_CMD || phase[i] == PHASE_STOP)
			break ;
		// if phase = phase back slash delete the \n at the end
		prompt_type = choose_prompt_type(0, phase[i]);
		if (phase[i] == PHASE_BACKSLASH)
		{
			cmd = delete_line_feed_at_the_end_of_the_cmd_string(cmd);
			phase[i] = PHASE_CMD;
		}
		if (phase[i] == PHASE_CMDSUBST || phase[i] == PHASE_BRACEPARAM) // debug
			cmd = delete_line_feed_at_the_end_of_the_cmd_string(cmd);
	}
	return (cmd);
}

int get_user_token(t_token **tk_lst)
{
	char *whole_cmd;
	char *cmd;
	int ret;
	t_lex_value lex_value;

	whole_cmd = NULL;
	ret = EXIT_SUCCESS;
	lex_value = LEX_CMD;
	while ("user is editing")
	{
		if ((cmd = get_command(lex_value)) == NULL)
		{
			ret = EXIT_FAILURE;
			break ;
		}
		lex_value = lexical_analysis_and_syntax_analysis(cmd, tk_lst, lex_value, 0);
		if (lex_value == LEX_FAILURE || ft_strequ(cmd, ENTER_KEY))
			free(cmd);
		else
			whole_cmd = ft_strjoin_and_free_2strings(whole_cmd, cmd);
		if (lex_value == LEX_SUCCESS || lex_value == LEX_FAILURE)
		{
			ret = lex_value;
			break ;
		}
	}
	if (whole_cmd)
		g_shell.history->tmp = whole_cmd;
	return (ret);
}

void reset_value(t_token **tk_lst, t_astnode **ast)
{
	(*tk_lst != NULL) ? clear_token(*tk_lst) : 0;
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
		if ((get_user_token(&tk_lst)) == EXIT_FAILURE)
			continue ;
		print_token(tk_lst);
		if ((ast = semantic_analysis(tk_lst)) == NULL)
			continue ;
		if (find_heredoc(ast) == EXIT_FAILURE)
			continue ;
		g_shell.first_heredoc = g_shell.heredoc_lst;
		printBinaryTree(ast);
		signal(SIGINT, SIG_DFL);
		executor(ast);
		signal(SIGINT, sig_int_handler);
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
	g_shell.alias = (t_alias**)malloc(sizeof(t_alias*) + 1);
	g_shell.alias[0] = NULL;
	g_shell.last_alias = NULL;
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
