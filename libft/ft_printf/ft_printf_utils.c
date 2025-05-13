/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 16:16:26 by alechin           #+#    #+#             */
/*   Updated: 2025/03/03 11:02:59 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
pf_putchar is just putchar 'c'
e_long is just long but I can't name it "long" 'u'
count_d is to count the integars 'i' 'd'
pf_putstr 's'
and recursive_hexa is to handle hexadecimals' 'x'
*/

#include "ft_printf.h"

void	pf_putchar(char c)
{
	write(1, &c, 1);
}

int	e_long(unsigned long num)
{
	int	count;

	count = 0;
	if (num > 9)
		count += e_long(num / 10);
	pf_putchar((num % 10) + '0');
	return (count + 1);
}

int	count_d(int n)
{
	int	count;

	count = 1;
	if (n == -2147483648)
	{
		pf_putchar('-');
		pf_putchar('2');
		n = 147483648;
		count += 2;
	}
	if (n < 0)
	{
		pf_putchar('-');
		n = -n;
		count++;
	}
	if (n > 9)
		count += count_d(n / 10);
	pf_putchar((n % 10) + '0');
	return (count);
}

int	pf_putstr(char *s)
{
	int	i;

	i = 0;
	if (!s)
	{
		if (write (1, "(null)", 6) == -1)
			return (-1);
		return (6);
	}
	if (s[0] == '\0')
		return (0);
	while (s[i])
	{
		write(1, &s[i], 1);
		i++;
	}
	return (i);
}

int	recursive_hexa(unsigned int num, char specfs)
{
	int	value;

	value = 0;
	if (num == 0)
	{
		pf_putchar('0');
		return (1);
	}
	if (num >= 16)
		value += recursive_hexa(num / 16, specfs);
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
