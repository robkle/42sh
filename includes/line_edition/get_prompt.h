/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_prompt.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihwang <ihwang@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/04 23:40:12 by marvin            #+#    #+#             */
/*   Updated: 2020/10/05 00:46:14 by ihwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_PROMPT_H
# define GET_PROMPT_H

# include <limits.h>
# include "utilities.h"
# include "libft.h"

# define PMPT_INIT "\033[0m"
# define PMPT_BOLD "\033[1m"
# define PMPT_RED "\033[31m"
# define PMPT_GREN "\033[32m"
# define PMPT_YELW "\033[33m"
# define PMPT_BLUE "\033[34m"
# define PMPT_MGTA "\033[35m"
# define PMPT_CYAN "\033[36m"
# define PMPT_GRSS "\033[92m"
# define PMPT_TMGT "\033[95m"
# define PMPT_SKYB "\033[96m"

size_t					get_prompt(void);

#endif
