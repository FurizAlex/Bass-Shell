/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alechin <alechin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 17:18:16 by alechin           #+#    #+#             */
/*   Updated: 2024/11/29 12:36:19 by alechin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
Name

itoa

int itoa(int n);

Description

Allocates (with malloc(3)) and returns a string
representing the integer received as an argument.
Negative numbers must be handled.

Return Value

The string representing the integer.
NULL if the allocation fails.
*/

#include "libft.h"

static int	locate_size(int *og, int *is_negative)
{
	int	result;
	int	n;

	n = *og;
	result = 1;
	if (n < 0)
	{
		*is_negative = 1;
		*og *= -1;
		n *= -1;
	}
	while (n > 9)
	{
		result++;
		n = n / 10;
	}
	if (*is_negative)
		return (result + 1);
	return (result);
}

static void	ft_str_reverse(char *str, int size)
{
	int		i;
	int		j;
	char	dummy;

	i = 0;
	j = size - 1;
	while (i < j)
	{
		dummy = str[i];
		str[i] = str[j];
		str[j] = dummy;
		i++;
		j--;
	}
}

static char	*check_edge_case(int n)
{
	char	*result;

	if (n == -2147483648)
	{
		result = malloc(sizeof(char) * 12);
		if (!result)
			return (NULL);
		ft_memmove(result, "-2147483648", 12);
		return (result);
	}
	if (n == 0)
	{
		result = malloc(sizeof(char) * 2);
		if (!result)
			return (NULL);
		ft_memmove(result, "0", 2);
		return (result);
	}
	return (NULL);
}

char	*ft_itoa(int n)
{
	int		size;
	int		is_negative;
	int		i;
	char	*result;

	result = check_edge_case(n);
	if (result)
		return (result);
	i = 0;
	is_negative = 0;
	size = locate_size(&n, &is_negative) + 1;
	result = malloc(sizeof(char) * size);
	if (!result)
		return (NULL);
	while (n > 0)
	{
		result[i++] = (n % 10) + '0';
		n = n / 10;
	}
	if (is_negative)
		result[i++] = '-';
	result[i] = '\0';
	ft_str_reverse(result, size - 1);
	return (result);
}
/*
#include <stdio.h>
int	main(void)
{
	int	numbers[] = {123, -123, 0, 214783647, -214783647};
	int	i = 0;

	while (i < 5)
	{
		char *str = ft_itoa(numbers[i]);
		printf("integar: %d -> s: %s\n", numbers[i], str);
		free(str);
		i++;
	}
	return (0);
}*/
