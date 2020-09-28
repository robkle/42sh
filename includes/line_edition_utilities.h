/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_edition_utilities.h                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihwang <ihwang@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/26 21:29:59 by marvin            #+#    #+#             */
/*   Updated: 2020/09/26 21:44:34 by ihwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LINE_EDITION_UTILITIES_H
# define LINE_EDITION_UTILITIES_H

# include <fcntl.h>
# include <term.h>
# include "libft.h"

void					apply_termcap_str(char *str, int x, int y);
size_t					get_current_row(void);
size_t					get_current_column(void);

#endif
