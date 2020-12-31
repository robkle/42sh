/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inhibitor.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthan <dthan@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/30 19:22:41 by dthan             #+#    #+#             */
/*   Updated: 2020/12/31 17:48:49 by dthan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INHIBITOR_H
# define INHIBITOR_H

int		is_open_dquote(char *input, int level, char *quote);
int		is_open_back_slash(char *input);
int is_real_quote(char *str, int i);
#endif
