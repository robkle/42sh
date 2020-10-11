/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tcgetsetpgrp.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthan <dthan@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/22 20:41:08 by marvin            #+#    #+#             */
/*   Updated: 2020/10/05 05:15:53 by dthan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int     ft_tcsetpgrp (int fd, pid_t pgrp_id)
{
  return ioctl (fd, TIOCSPGRP, &pgrp_id);
}

pid_t   ft_tcgetpgrp (int fd)
{
  int pgrp;
  if (ioctl (fd, TIOCGPGRP, &pgrp) < 0)
    return (pid_t) -1;
  return (pid_t) pgrp;
}
