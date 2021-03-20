/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   constant.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihwang <ihwang@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/14 09:43:57 by dthan             #+#    #+#             */
/*   Updated: 2021/03/20 03:07:49 by ihwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONSTANT_H
# define CONSTANT_H
# include <limits.h>

/*
**	The constant will be added in this file for making maintaning easier
**	[MAX_ARGV = 256], for inceasing the speed of the shell
**	[READ_END = 0] and [WRITE_END = 1], using in pipe
**	[PARENT = 1] and [CHILD 0] mean parent process and child process
*/

# define MAX_HASH 200
# define MAX_ARGV 256
# define READ_END 0
# define WRITE_END 1
# define PARENT 1
# define CHILD 0
# define SHELL_NAME "42sh"

# define SAVED_STDIN 0
# define SAVED_STDOUT 1
# define SAVED_STDERR 2

# define BUFF_LINE_EDITION 8

/*
** Color for the prompt
*/
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

# define F_TYPE_MASK 0170000
# define KEY 1
# define VAL 0
# define TRUE 1
# define FALSE 0

#endif
