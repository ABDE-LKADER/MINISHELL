/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_plus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abadouab <abadouab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 19:19:43 by abadouab          #+#    #+#             */
/*   Updated: 2024/04/19 11:34:56 by abadouab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mylib.h"

static int	address_plus(unsigned long num)
{
	int		len;
	char	*base;

	len = 0;
	base = "0123456789abcdef";
	if (num > 15)
		len += address_plus(num / 16);
	len += print_char(base[num % 16]);
	return (len);
}

int	print_address(void *ptr)
{
	int	len;

	len = 0;
	len += print_string("0x");
	len += address_plus((unsigned long)ptr);
	return (len);
}

int	print_num(int num)
{
	int				len;
	unsigned int	number;

	len = 0;
	if (num < 0)
	{
		number = -num;
		len += print_char('-');
	}
	else
		number = num;
	if (number > 9)
		len += print_unum(number / 10);
	len += print_char(number % 10 + 48);
	return (len);
}

int	print_unum(unsigned int num)
{
	int	len;

	len = 0;
	if (num > 9)
		len += print_unum(num / 10);
	len += print_char(num % 10 + 48);
	return (len);
}

int	print_hex(unsigned int num, char set)
{
	int		len;
	char	*base;

	len = 0;
	base = NULL;
	if (set == 'x')
		base = "0123456789abcdef";
	else if (set == 'X')
		base = "0123456789ABCDEF";
	if (num > 15)
		len += print_hex(num / 16, set);
	len += print_char(base[num % 16]);
	return (len);
}
