/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alias_substitution.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgrankul <vgrankul@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/15 23:35:55 by vgrankul          #+#    #+#             */
/*   Updated: 2020/10/05 04:14:12 by vgrankul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

char	*is_alias(char *str)
{
	int i;

	i = 0;
	while(g_alias[i] != NULL)
	{
		if (ft_strcmp(g_alias[i]->name, str) == 0)
			return (g_alias[i]->value);
		i++;
	}
	return (NULL);
}

int alias_substitution(t_token *current_token, t_token **prev_token, t_token **token_lst)
{
    char *alias_substr;
    t_token *lst;

    alias_substr = NULL;
    lst = NULL;
    if ((*prev_token) == NULL || ((*prev_token) != NULL && is_control_op_not_newline((*prev_token)->type) == 1))
    {
        if ((alias_substr = is_alias(current_token->data)) != NULL)
        {
            clear_token(current_token);
            lst = lexer_and_parser(alias_substr);
            while(lst != NULL)
            {
                add_token_into_token_list(token_lst, lst);
                if (!parser(lst, *(prev_token)))
			    {
				    clear_token(lst);
                    //return NULL?
			    }
			    *prev_token = lst;
                lst = lst->next;
            }
            print_token(*token_lst);
            return (1);
        }
    }
    return (0);
}