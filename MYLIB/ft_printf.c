/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abadouab <abadouab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 09:24:30 by abadouab          #+#    #+#             */
/*   Updated: 2024/04/19 14:52:35 by abadouab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mylib.h"

int	print_char(char c)
{
	return (ft_putchar_fd(c, 1), 1);
}

int	print_string(char *str)
{
	if (!str)
		str = "(null)";
	return (ft_putstr_fd(str, 1), ft_strlen(str));
}

static int	format_set(char format, va_list lstarg)
{
	int	print;

	print = 0;
	if (format == 'c')
		print += print_char(va_arg(lstarg, int));
	else if (format == 's')
		print += print_string(va_arg(lstarg, char *));
	else if (format == 'p')
		print += print_address(va_arg(lstarg, void *));
	else if (format == 'd' || format == 'i')
		print += print_num(va_arg(lstarg, int));
	else if (format == 'u')
		print += print_unum(va_arg(lstarg, unsigned int));
	else if (format == 'x' || format == 'X')
		print += print_hex(va_arg(lstarg, unsigned int), format);
	else if (format == '%')
		print += print_char(format);
	return (print);
}

int	ft_printf(const char *format, ...)
{
	int		print;
	va_list	lstarg;

	print = 0;
	if (write(1, format, 0) == -1)
		return (-1);
	va_start(lstarg, format);
	while (*format)
	{
		if (*format == '%' && ft_strchr(SPECIFIERS, *(format + 1)))
			print += format_set(*(++format), lstarg);
		else
			print += print_char(*format);
		format++;
	}
	return (va_end(lstarg), print);
}
