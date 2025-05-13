/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_second_utils.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/03 10:45:11 by alechin           #+#    #+#             */
/*   Updated: 2025/03/03 11:02:46 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
hdle_ptr = 'p'
im too lazy to write the rest man look I just finished printf ok??
*/

#include "ft_printf.h"

int	hdle_ptr(void *ptr)
{
	int				idx;
	uintptr_t		addr;

	idx = 0;
	addr = (uintptr_t)ptr;
	if (ptr == NULL)
	{
		write(1, "(nil)", 5);
		return (5);
	}
	write(1, "0x", 2);
	idx = recursive_hexa_uint(addr, 'x');
	return (idx + 2);
}

int	pf_percent(void)
{
	write (1, "%", 1);
	return (1);
}

int	recursive_hexa_uint(uintptr_t num, char specfs)
{
	int	value;

	value = 0;
	if (num == 0)
	{
		pf_putchar('0');
		return (1);
	}
	if (num >= 16)
		value += recursive_hexa_uint(num / 16, specfs);
	if (specfs == 'x')
	{
		pf_putchar("0123456789abcdef"[num % 16]);
	}
	else if (specfs == 'X')
	{
		pf_putchar("0123456789ABCDEF"[num % 16]);
	}
	return (value + 1);
}
