/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexical_analysis.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthan <dthan@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/09 08:37:27 by dthan             #+#    #+#             */
/*   Updated: 2021/03/06 19:15:46 by dthan            ###   ########.fr       */
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

t_token	*destroy_lexical_service_struct(t_lexical_service self)
{
	(self.tk) ? clear_token(self.tk) : 0;
	(self.stream) ? clear_token(self.stream) : 0;
	return (NULL);
}

t_token	*lexical_analysis_service(char *input, char *alias, int sub)
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
			if (alias && ft_strequ(alias, find_alias_str(self.tk->data)))
				return (destroy_lexical_service_struct(self));
			alias_substitution(&(self.tk), &(self.prev_tk),
				(alias == NULL) ? (self.tk)->data : alias);
			if (self.tk == NULL)
				continue;
		}
		else
			self.prev_tk = self.tk;
		add_token_into_token_list(&(self.stream), self.tk);
	}
	return (self.stream);
}
