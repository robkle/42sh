/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexical_analysis.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthan <dthan@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/09 08:37:27 by dthan             #+#    #+#             */
/*   Updated: 2021/03/07 05:15:46 by dthan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	init_lexical_service_struct(t_lexical_service *self)
{
	self->i = 0;
	self->stream = NULL;
	self->tk = NULL;
	self->prev_tk = NULL;
}

int		alias_requirement(t_lexical_service self, int sub)
{
	if (sub == 0 &&
		self.tk->type == TOKEN_WORD &&
		is_alias(self.tk->data, self.prev_tk))
		return (1);
	return (0);
}

t_token	*alias_infinite_loop(t_lexical_service *self)
{
	ft_dprintf(2, "%s: alias: infinite loop\n", SHELL_NAME);
	add_token_into_token_list(&(self->stream), self->tk);
	return (self->stream);
}

t_token	*lexical_analysis_service(char *input, char *fix_alias_name, int sub)
{
	t_lexical_service self;

	init_lexical_service_struct(&self);
	while (input[self.i])
	{
		if (input[self.i] == ' ' || input[self.i] == '\t')
		{
			self.i++;
			continue;
		}
		self.tk = token_creator_service(input, &(self.i), self.prev_tk);
		if (alias_requirement(self, sub))
		{
			if (fix_alias_name && ft_strequ(fix_alias_name, self.tk->data))
			{
				free(self.tk->data);
				self.tk->data = ft_strdup(fix_alias_name);
				self.prev_tk = self.tk;
			}
			else
			{
				alias_substitution(&self, (fix_alias_name == NULL) ? (self.tk)->data : fix_alias_name);
				continue;
			}
		}
		else
			self.prev_tk = self.tk;
		add_token_into_token_list(&(self.stream), self.tk);
	}
	return (self.stream);
}
