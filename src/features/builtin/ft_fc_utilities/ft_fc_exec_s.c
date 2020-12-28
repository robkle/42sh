/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fc_exec_s.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthan <dthan@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/22 13:43:48 by dthan             #+#    #+#             */
/*   Updated: 2020/12/23 19:16:59 by dthan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static char *fc_s_replace_replace(char *target, char *needle, char *replacement)
{
	char buffer[1024];
	char *tmp;
	char *insert_point;
	char *p;

	ft_bzero(buffer, 1024);
	tmp = target;
	insert_point = &buffer[0];
	while(1) {
		p = ft_strstr(tmp, needle);
		if (p == NULL)
		{
			ft_strcpy(insert_point, tmp);
			break;
		}
		ft_memcpy(insert_point, tmp, p - tmp);
		insert_point += p - tmp;
		ft_memcpy(insert_point, replacement, ft_strlen(replacement));
		insert_point += ft_strlen(replacement);
		tmp = p + ft_strlen(needle);
	}
	return (strdup(buffer));
}

static char *fc_s_replace_repeat(char *str, char *replacement)
{
	char buffer[1024];
	int i;
	int len;

	ft_bzero(buffer, 1024);
	i = 0;
	len = ft_strlen(str);
	while (i++ < len)
		ft_strcat(buffer, replacement);
	return (strdup(buffer));
}

static char *fc_s_replace_delete(char *target, char *needle)
{
	char buffer[1024];
	char *tmp;
	char *insert_point;
	char *p;

	ft_bzero(buffer, 1024);
	tmp = target;
	insert_point = &buffer[0];
	while(1) {
		p = ft_strstr(tmp, needle);
		if (p == NULL)
		{
			ft_strcpy(insert_point, tmp);
			break;
		}
		ft_memcpy(insert_point, tmp, p - tmp);
		insert_point += p - tmp;
		tmp = p + ft_strlen(needle);
	}
	return (strdup(buffer));
}

/*
** function fc_s_replace
** @old : the string in the cmd will be replace
** @new : the new string will replace the old sub string which is in the cmd
** 		4 cases:
**			no string old, no string new
**			there is string old but not string new
**			there is string new but not string old
**			there are both string new and string old
**	How to handle them:
**		case 1: no string old and no string new
**			return error since it will cause the infinite loop, same happend in any
**			example shell
**		case 2: there is string old but not string new
**			Apply the delete process, so, going throw the cmd, if there is apearance
**			of string old in the cmd, then these sub strings will be delete
**		case 3: there is string new but not string old
**			Apply the replace but every character of the cmd will be replace by string
**			new
**		case 4: there are both string new and string old
**			Apply replacing the cmd string like normal
*/

static char *fc_s_replace(char *str, char *cmd)
{
	char *temp;
	char *old;
	char *new;

	temp = cmd;
	old = ft_strndup(str, ft_strlen(str) - ft_strlen(ft_strchr(str, '=')));
	new = ft_strdup((ft_strchr(str, '=')) + 1);
	if (ft_strlen(old) == 0 && ft_strlen(new) == 0)
		cmd = NULL;
	else if (ft_strlen(old) == 0 && ft_strlen(new) != 0)
		cmd = fc_s_replace_repeat(cmd, new);
	else if (ft_strlen(old) != 0 && ft_strlen(new) == 0)
		cmd = fc_s_replace_delete(cmd, old);
	else
		cmd = fc_s_replace_replace(cmd, old, new);
	(temp) ? free(temp) : 0;
	(old) ? free(old) : 0;
	(new) ? free(new) : 0;
	return (cmd);
}

static char *fc_return_cmd(char *str)
{
	int pos;

	pos = fc_range(str);
	if (pos == 0)
		return (NULL);
	return (ft_strdup(g_shell.history->hist[pos - 1]));
}

/*
** @FC with s option
**	SYNOPSIS: fc -s [old=new] [first]
**		1. We need to find the command, and it can be found in 2 different way
**				which depends on the input of `first` block
**			+ if the first block is number with the  condition of, first character
**			is a digit or the first is '-' and the next character is digit. After
**			that the finding command will be processed with the procedure like this
**			. IF the position aquired of the input, is out of range from 1 to the
**			last command, it will return the position of the last command no matter
**			what
**			+ else, it will go to the function fc_find_existing_cmd and find in the
**			history if there is any command match with the input.
**		2. We check the returned value of cmd, in the first way, there is always an
**			correct return, however in the 2nd way, the return value can be NULL since
**			there is no matching command in the history database then an error will be
**			issued : no command found
**		3. If the 2nd step is correct and there is a cmd return, it will check if there
**			is the replace block else move on. If there is the replace block, we will
**			extract the old and new part and replace it into the cmd that we just found
**			by using the funtion fc_s_replace
**		4. Execute the command and return EXIT_SUCCESS
*/

int fc_s_op(char *replace, char *first)
{
	char	*cmd;

	cmd = fc_return_cmd(first);
	if (cmd == NULL)
		return (fc_error_no_command_found());
	if (replace)
	{
		cmd = fc_s_replace(replace, cmd);		
		if (cmd == NULL)
		{
			ft_dprintf(2, "%s: fc: both old and new can not be empty\n");
			return (EXIT_FAILURE);
		}
	}
	ft_printf("%s\n", cmd);
	ft_execute(cmd);
	if (g_shell.history->tmp)
		free(g_shell.history->tmp);
	g_shell.history->tmp = cmd;
	return (EXIT_SUCCESS);
}
