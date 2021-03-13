/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fc_exec_e.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthan <dthan@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/22 14:30:35 by dthan             #+#    #+#             */
/*   Updated: 2021/03/13 00:28:54 by dthan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static int fc_is_accessible_editor(char *editor, char **options)
{
	int i;
	char path[4096];

	i = -1;
	ft_bzero(path, 4096);
	while (options && options[++i])
	{
		ft_strcpy(path, options[i]);
		ft_strcat(path, "/");
		ft_strcat(path, editor);
		if (access(path, F_OK) == 0)
			return (1);
	}
	return (0);
}

static int fc_check_editor(char *editor)
{
	char **options;

	options = ft_strsplit(ft_getenv("PATH"), ':');
	if (!fc_is_accessible_editor(editor, options))
	{
		ft_dprintf(2, "%s: %s: command not found\n", SHELL_NAME, editor);
		ft_arraydel(options);
		return (EXIT_FAILURE);
	}
	ft_arraydel(options);
	return (EXIT_SUCCESS);
}

static char *fc_e_build_cmd(void)
{
	char *line;
	char cmd[4096];
	int fd;

	ft_bzero(cmd, 4096);
	fd = open(FC_EDITING_FILE, O_RDONLY, 0644);
	while (get_next_line(fd, &line))
	{
		if (cmd[0] && !ft_check_cont(cmd)) //need to check this
			ft_strcat(cmd, ";");
		ft_strcat(cmd, line);
		if (ft_check_cont(cmd))
			ft_strcat(cmd, "\n");
		free(line);
	}
	close(fd);
	return (ft_strdup(cmd));
}

static int fc_e_init_range(int *r_ind, char *first, char *last)
{
	r_ind[0] = g_shell.history->curr;
	r_ind[1] = g_shell.history->curr;
	if (first)
	{
		r_ind[0] = fc_range(first);
		if (r_ind[0] == 0)
			return (fc_error_history_specification_out_of_range());
		r_ind[1] = r_ind[0];
		if (last)
		{
			r_ind[1] = fc_range(last);
			if (r_ind[1] == 0)
				return (fc_error_history_specification_out_of_range());
		}
	}
	return (EXIT_SUCCESS);
}

static void fc_e_copy_lines_into_editor(int *r_ind)
{
	int fd;

	fd = open(FC_EDITING_FILE, O_CREAT | O_TRUNC | O_WRONLY, 0644);
	if (r_ind[0] < r_ind[1])
		while (r_ind[0] < r_ind[1])
			ft_dprintf(fd, "%s\n", g_shell.history->hist[r_ind[0]++ - 1]);	
	else if (r_ind[0] > r_ind[1])
		while (r_ind[0] > r_ind[1])
			ft_dprintf(fd, "%s\n", g_shell.history->hist[r_ind[0]-- - 1]);
	ft_dprintf(fd, "%s", g_shell.history->hist[r_ind[0] - 1]);
	close(fd);
}

static void fc_e_editing_process(char *editor)
{
	char cmd[4096];

	ft_bzero(cmd, 4096);
	ft_strcpy(cmd, editor);
	ft_strcat(cmd, " ");
	ft_strcat(cmd, FC_EDITING_FILE);
	ft_fc_execute(cmd);
}

/*
** FC with e option
**  SYNOPSIS: fc [-r] [-e editor] [first [last]]
**	@ops: the option to check if there is -r option
**	@editor: to check the editor
**	@first: to check the first block
**	@last: to check the last block
** 		1. Check the editor string value if the input editor is valid
**		if the editor is invalid, then return error with a command not
**		found message. If editor is valid move on to the next steps
**		2. Init the range of first and last
**		3. Swap if there is R option
**		4. execute the editor
**		5. build the command
**		6. execute and change the command with g_shell.history->tmp 
*/

int fc_e_op(int ops, char *editor, char *first, char *last)
{
	char	*cmd;
	int r_ind[2];

	if (fc_check_editor(editor) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (fc_e_init_range(r_ind, first, last) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (ops & FC_R_OP)
		ft_swap_int(&r_ind[0], &r_ind[1]);
	fc_e_copy_lines_into_editor(r_ind);
	fc_e_editing_process(editor);
	cmd = fc_e_build_cmd();
	if (g_shell.history->tmp)
		free(g_shell.history->tmp);
	g_shell.history->tmp = cmd;
	ft_fc_execute(cmd);
	return (EXIT_SUCCESS);
}
