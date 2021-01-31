/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tcsetpgrp.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthan <dthan@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/26 13:40:48 by dthan             #+#    #+#             */
/*   Updated: 2021/01/28 16:23:44 by dthan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/ioctl.h>
#include <sys/types.h>

int	ft_tcsetpgrp(int fd, pid_t pgrp_id)
{
	return (ioctl(fd, TIOCSPGRP, &pgrp_id));
}
