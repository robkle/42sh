/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   core.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthan <dthan@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/18 02:33:13 by dthan             #+#    #+#             */
/*   Updated: 2020/12/26 19:09:26 by dthan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

int	parse_and_print(const char *format, va_list args, size_t *pos, int fd)
{
	t_info	info;
	int		position_copy;
	char	*str;

	position_copy = *pos;
	if (format[*pos] == '\0')
		return (0);
	parsing(format, args, pos, &info);
	if (info.specifier == spec_none)
	{
		if (args)
		{
			*pos = position_copy + 1;
			str = ft_itoa_signed_longlong((long long)info.dup_first_args);
			write(fd, "%", 1);
			write(fd, str, ft_strlen(str));
			free(str);
			return (ft_strlen(str) + 2);
		}
		*pos = position_copy;
		write(fd, "%", 1);
		return (0);
	}
	return (printing(&info, args, fd));
}

int	full_str_printing(const char *format, va_list args, int fd)
{
	size_t	pos;
	int		len;
	int		spurious_traling_case;

	pos = 0;
	len = 0;
	spurious_traling_case = 0;
	while (format[pos] != '\0')
	{
		if (format[pos] != '%')
		{
			write(fd, &format[pos++], 1);
			len++;
		}
		else
		{
			pos++;
			len += parse_and_print(format, args, &pos, fd);
			if (len < spurious_traling_case)
				return (-1);
		}
		spurious_traling_case = len;
	}
	return (len);
}

int	ft_printf(const char *format, ...)
{
	int		printed;
	va_list	args;

	va_start(args, format);
	printed = full_str_printing(format, args, STDOUT_FILENO);
	va_end(args);
	return (printed);
}

int	ft_dprintf(int fd, const char *format, ...)
{
	int		printed;
	va_list	args;

	va_start(args, format);
	printed = full_str_printing(format, args, fd);
	va_end(args);
	return (printed);
}
