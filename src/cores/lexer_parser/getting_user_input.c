/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getting_user_input.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthan <dthan@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/06 18:19:29 by dthan             #+#    #+#             */
/*   Updated: 2021/03/07 01:44:49 by dthan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

/*
typedef struct s_get_command_service
{
	t_phase phase[20];
	int i;
	char *cmd;
	char *line;
	t_prompt prompt_type;	
}	t_get_command_service;

void init_get_command_service_struct(t_get_command_service *self, t_lex_value lex_value)
{
	ft_bzero(self->phase, 20);
	self->i = 0;
	self->cmd = NULL;
	self->line = NULL;
	self->prompt_type = choose_prompt_type(lex_value, 0);
}

char *get_command(t_lex_value lex_value)
{
	t_get_command_service instance;

	init_get_command_service_struct(&instance, lex_value);
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
