/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_indicator.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihwang <ihwang@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/18 20:29:42 by marvin            #+#    #+#             */
/*   Updated: 2020/10/18 20:30:57 by ihwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGNAL_INDICATOR_H
# define SIGNAL_INDICATOR_H

typedef enum
{
	SIGINT_INDICATOR = (1 << 0),
	SIGWINCH_INDICATOR = (1 << 1),
}	t_signal_indicator;

#endif
