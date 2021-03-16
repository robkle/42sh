/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getting_user_input.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthan <dthan@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/06 18:19:29 by dthan             #+#    #+#             */
/*   Updated: 2021/03/14 02:32:44 by dthan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static void	init_get_command_service_struct(
	t_get_command_service *self, t_lex_value lex_value)
{
	ft_bzero(self->phase, 20);
	self->i = 0;
	self->cmd = NULL;
	self->line = NULL;
	self->prompt_type = choose_prompt_type(lex_value, 0);
}

static char	*destroy_get_command_service_struct(t_get_command_service self)
{
	(self.cmd) ? free(self.cmd) : 0;
	(self.line) ? free(self.line) : 0;
	return (NULL);
}

char		*get_command(t_lex_value lex_value)
{
	t_get_command_service self;

	init_get_command_service_struct(&self, lex_value);
	while ("command editting")
	{
		if ((self.line = ft_get_line(&self.phase[self.i], self.prompt_type,
			lex_value)) == NULL)
			return (destroy_get_command_service_struct(self));
		if (self.phase[self.i] != PHASE_STOP)
			analyzing_phase(self.line, self.phase, &self.i);
		if (ft_hist_exp(&self.line, self.prompt_type))
			ft_printf("%s", self.line);
		self.cmd = ft_strjoin_and_free_2strings(self.cmd, self.line);
		if (self.phase[self.i] == PHASE_CMD || self.phase[self.i] == PHASE_STOP)
			break ;
		self.prompt_type = choose_prompt_type(0, self.phase[self.i]);
		if (self.phase[self.i] == PHASE_BACKSLASH)
		{
			self.phase[self.i--] = 0;
			self.cmd = delete_back_slash_and_line_feed(self.cmd);
		}
	}
	return (self.cmd);
}
