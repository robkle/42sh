/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_exp2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rklein <rklein@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/26 20:35:21 by rklein            #+#    #+#             */
/*   Updated: 2021/02/26 20:51:12 by rklein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int	ft_update_arx(char **arx, char **exp, int res)
{
	free(*arx);
	*arx = ft_strcombine(exp, ft_llitoa(res));
	return (ft_strlen(*arx));
}

int	ft_arx_free_exp(char **exp, char *arx)
{
	ft_arraydel(exp);
	free(arx);
	return (0);
}

int	ft_arx_free_exp_bracket(char *arx)
{
	ft_printf("42sh: %s: missing ')'\n", &arx[1]);
	free(arx);
	return (0);
}
