/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alechin <alechin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 12:11:35 by alechin           #+#    #+#             */
/*   Updated: 2024/11/29 14:07:10 by alechin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
Name

memcmp

Synopsis

#include <string.h>

void *memchr(const void *s, int c, size_t n);

Description

The memcmp() function compares the first n bytes 
(each interpreted as unsigned char) of the memory areas s1 and s2. 

Return Value

The memcmp() function returns an integer less than,
equal to, or greater than zero if the first n bytes of s1 is found, 
respectively, to be less than, to match, 
or be greater than the first n bytes of s2. 
*/

#include "libft.h"

int	ft_memcmp(const void *ptr1, const void *ptr2, size_t num)
{
	const unsigned char	*p1;
	const unsigned char	*p2;
	size_t				i;

	p1 = (const unsigned char *)ptr1;
	p2 = (const unsigned char *)ptr2;
	i = 0;
	while (i < num)
	{
		if (p1[i] != p2[i])
		{
			return (p1[i] - p2[i]);
		}
		i++;
	}
	return (0);
}
/*
#include <stdio.h>
int	main(void)
{
	char	*str = "Hello, world";
	char	*a2str = "Hello, wod";
	int	arr[5] = {1234325234, 1235342532, 12345814};
	int	arr2[5] = {1234325234, 1235342532, 123458134};

	printf("%d\n", ft_memcmp(str, a2str, 5));
	printf("%d\n", ft_memcmp(str, a2str, 10));
	printf("%d\n", ft_memcmp(arr, arr2, 8));
	printf("%d\n", ft_memcmp(arr, arr2, 12));
	return (0);
}*/
